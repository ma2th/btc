// Copyright 2018 Matthias Ring
// Machine Learning and Data Analytics Lab
// Friedrich-Alexander-University Erlangen-Nuremberg
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#if PLATFORM_IOS

#include "BTCConfiguration.h"
#include "IOSAsyncTask.h"

#import "BTCViewController.h"

@interface BTCViewController ()

@end

@implementation BTCViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
#ifdef USE_SOUND_BUTTONS
    // Do not reset on deactivation because mute event seems
    // to get fired only after viewDidLoad, not after viewDidAppear
    self.skipFirstTwoMuteEvents = 2;
    
    [self captureAudioButtons];
#endif
    
#ifdef USE_ENTER_BUTTON
    [self captureEnterKey];
#endif
}

#ifdef USE_SOUND_BUTTONS
- (void) captureAudioButtons {
    MPVolumeView* volumeView = nil;
    MPRemoteCommandCenter *remoteCommandCenter = nil;
        
    volumeView = [[MPVolumeView alloc] initWithFrame: CGRectMake(-1000, -1000, 200, 20)];
    [self.view addSubview: volumeView];
    
    for (UIView *view in [volumeView subviews]){
        if ([[view.class description] isEqualToString:@"MPVolumeSlider"]){
            self.volumeSlider = (UISlider*)view;
            self.volumeSlider.userInteractionEnabled = NO;
            break;
        }
    }
    
    [self activateAudioSession];
    [self resetVolumeSlider];
    
    [self.volumeSlider addTarget:self action:@selector(volumeSliderChanged:) forControlEvents:UIControlEventValueChanged];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(audioSessionInterupted:) name:AVAudioSessionInterruptionNotification object:nil];
    
    remoteCommandCenter = [MPRemoteCommandCenter sharedCommandCenter];
    [[remoteCommandCenter togglePlayPauseCommand] addTarget:self action:@selector(togglePlayPause)];
}

- (void) activateAudioSession {
    NSError *sessionError = nil;
    AVAudioSession *audioSession = nil;
    
    audioSession = [AVAudioSession sharedInstance];
    [audioSession setActive:YES error:&sessionError];
    if (sessionError) {
        NSLog(@"Cannot activate audio session: %@", sessionError);
    }
}

- (void) volumeSliderChanged:(UISlider *)sender {
    if (self.volumeSlider.value == 0.5 && self.lastVolumeValue == 0.5) {
        return;
    }
    
    if (self.volumeSlider.value == 0) {
        if (self.skipFirstTwoMuteEvents <= 0) {
            [FIOSAsyncTask CreateTaskWithBlock : ^ bool(void) {
                _queue->Enqueue(BTCEventMapping::MUTE);
                return true;
            }];
            [self resetVolumeSlider];
        } else {
            NSLog(@"Skipping mute event on purpose as it is always fired automatically after initialization");
            self.skipFirstTwoMuteEvents--;
        }
    } else if (self.volumeSlider.value > self.lastVolumeValue) {
        [FIOSAsyncTask CreateTaskWithBlock : ^ bool(void) {
            _queue->Enqueue(BTCEventMapping::VOLUME_UP);
            return true;
        }];
        [self resetVolumeSlider];
    } else if (self.volumeSlider.value < self.lastVolumeValue) {
        [FIOSAsyncTask CreateTaskWithBlock : ^ bool(void) {
            _queue->Enqueue(BTCEventMapping::VOLUME_DOWN);
            return true;
        }];
        [self resetVolumeSlider];
    }
}

- (void) resetVolumeSlider {
    self.lastVolumeValue = 0.5f;
    [self.volumeSlider setValue:0.5f animated:NO];
}

- (void) togglePlayPause {
    [FIOSAsyncTask CreateTaskWithBlock : ^ bool(void) {
        _queue->Enqueue(BTCEventMapping::PLAY_PAUSE);
        return true;
    }];
}

- (void) audioSessionInterupted:(NSNotification*)notification {
    NSError *error = nil;
    NSInteger interuptionType;
    NSDictionary *userInfo = nil;
    
    userInfo = notification.userInfo;
    interuptionType = [[userInfo valueForKey:AVAudioSessionInterruptionTypeKey] integerValue];
    switch (interuptionType) {
        case AVAudioSessionInterruptionTypeBegan:
        {
            break;
        }
        case AVAudioSessionInterruptionTypeEnded:
        {
            [self activateAudioSession];
            break;
        }
        default:
        {
            break;
        }
    }
}
#endif

#ifdef USE_ENTER_BUTTON
- (void)viewDidAppear:(BOOL)animated {
    [self.textField becomeFirstResponder];
}

- (void) captureEnterKey {
    self.textField = [[UITextField alloc] initWithFrame:CGRectMake(-1000, -1000, 200, 20)];
    self.textField.delegate = self;
    [self.view addSubview: self.textField];
    
    [self.textField becomeFirstResponder];
}

//  UITextFieldDelegate
- (BOOL) textFieldShouldReturn:(UITextField *)textField {
    [FIOSAsyncTask CreateTaskWithBlock : ^ bool(void) {
        _queue->Enqueue(BTCEventMapping::ENTER);
        return true;
    }];
    return NO;
}
#endif

#ifdef USE_ARROW_BUTTONS
// UIResponder
- (NSArray<UIKeyCommand *>*) keyCommands {
    return @[[UIKeyCommand keyCommandWithInput:UIKeyInputDownArrow modifierFlags:0 action:@selector(arrowKeyPressed:)],
             [UIKeyCommand keyCommandWithInput:UIKeyInputUpArrow modifierFlags:0 action:@selector(arrowKeyPressed:)],
             [UIKeyCommand keyCommandWithInput:UIKeyInputLeftArrow modifierFlags:0 action:@selector(arrowKeyPressed:)],
             [UIKeyCommand keyCommandWithInput:UIKeyInputRightArrow modifierFlags:0 action:@selector(arrowKeyPressed:)]];
}

- (void) arrowKeyPressed:(UIKeyCommand *)sender {
    if ([UIKeyInputDownArrow isEqualToString:sender.input]) {
        [FIOSAsyncTask CreateTaskWithBlock : ^ bool(void) {
            _queue->Enqueue(BTCEventMapping::DOWN);
            return true;
        }];
    } else if ([UIKeyInputUpArrow isEqualToString:sender.input]) {
        [FIOSAsyncTask CreateTaskWithBlock : ^ bool(void) {
            _queue->Enqueue(BTCEventMapping::UP);
            return true;
        }];
    } else if ([UIKeyInputLeftArrow isEqualToString:sender.input]) {
        [FIOSAsyncTask CreateTaskWithBlock : ^ bool(void) {
            _queue->Enqueue(BTCEventMapping::LEFT);
            return true;
        }];
    } else if ([UIKeyInputRightArrow isEqualToString:sender.input]) {
        [FIOSAsyncTask CreateTaskWithBlock : ^ bool(void) {
            _queue->Enqueue(BTCEventMapping::RIGHT);
            return true;
        }];
    }
}
#endif

@end

#endif
