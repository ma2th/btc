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

#include "Queue.h"
#include "BTCConfiguration.h"

#if PLATFORM_IOS

#import <UIKit/UIKit.h>
#import <AVFoundation/AVAudioSession.h>
#import <MediaPlayer/MediaPlayer.h>

@interface BTCViewController : UIViewController
#ifdef USE_ENTER_BUTTON
<UITextFieldDelegate>
#endif

@property class TQueue<FGamepadKeyNames::Type>* queue;

#ifdef USE_ENTER_BUTTON
@property (nonatomic, assign) UITextField* textField;

- (void) captureEnterKey;
#endif

#ifdef USE_ARROW_BUTTONS
- (void) arrowKeyPressed:(UIKeyCommand *)sender;
#endif

#ifdef USE_SOUND_BUTTONS
@property (nonatomic, assign) float lastVolumeValue;
@property (nonatomic, assign) UISlider* volumeSlider;

- (void) captureAudioButtons;
- (void) volumeSliderChanged:(UISlider *)sender;
- (void) resetVolumeSlider;
- (void) togglePlayPause;
- (void) activateAudioSession;
- (void) audioSessionInterupted:(NSNotification*)notification;
#endif

@end

#endif
