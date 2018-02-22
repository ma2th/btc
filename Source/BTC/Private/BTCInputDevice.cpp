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

#include "BTCInputDevice.h"
#include "InputCoreTypes.h"

#if PLATFORM_IOS
#include "IOSView.h"
#include "IOSAppDelegate.h"
#include "BTCViewController.h"
#endif

FBTCInputDevice::FBTCInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& NewMessageHandler) :
MessageHandler(NewMessageHandler)
{
    AddViewController();
}

FBTCInputDevice::~FBTCInputDevice()
{
}

void FBTCInputDevice::AddViewController()
{
#if PLATFORM_IOS
    dispatch_async(dispatch_get_main_queue(), ^{
        IOSAppDelegate* appDelegate = [IOSAppDelegate GetDelegate];
        IOSViewController* viewController = appDelegate.IOSController;
        FIOSView* iOSView = appDelegate.IOSView;
        
        BTCViewController* btcController = [[BTCViewController alloc] init];
        [viewController addChildViewController:btcController];
        btcController.view.bounds = iOSView.bounds;
        btcController.queue = &EventQueue;
        [iOSView addSubview:btcController.view];
        [btcController didMoveToParentViewController: viewController];
    });
#endif
}

void FBTCInputDevice::SetMessageHandler(const TSharedRef< FGenericApplicationMessageHandler >& NewMessageHandler)
{
    this->MessageHandler = NewMessageHandler;
}

void FBTCInputDevice::Tick(float DeltaTime)
{
}

void FBTCInputDevice::SendControllerEvents()
{
    FGamepadKeyNames::Type Event;
    
    while (!EventQueue.IsEmpty())
    {
        EventQueue.Dequeue(Event);
        MessageHandler->OnControllerButtonPressed(Event, 0, false);
    }
}

bool FBTCInputDevice::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& OutputDevice)
{
    return false;
}

void FBTCInputDevice::SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value)
{
}

void FBTCInputDevice::SetChannelValues(int32 ControllerId, const FForceFeedbackValues &Values)
{
}
