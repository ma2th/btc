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

#pragma once

#include "CoreMinimal.h"
#include "IInputDevice.h"
#include "Queue.h"
#include "InputCoreTypes.h"

#if PLATFORM_IOS
#include "IOSView.h"
#include "IOSAppDelegate.h"
#include "BTCViewController.h"
#endif

class FBTCInputDevice : public IInputDevice
{
public:
    FBTCInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& NewMessageHandler, bool Active);
    ~FBTCInputDevice();
    
    virtual void SetMessageHandler(const TSharedRef< FGenericApplicationMessageHandler >& NewMessageHandler) override;
    virtual void Tick(float DeltaTime) override;
    virtual void SendControllerEvents() override;
    virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& OutputDevice) override;
    virtual void SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override;
    virtual void SetChannelValues(int32 ControllerId, const FForceFeedbackValues &Values) override;

    void Activate();
    void Deactivate();
    
private:
    TSharedRef<FGenericApplicationMessageHandler> MessageHandler;
    TQueue<FGamepadKeyNames::Type> EventQueue;
    
#if PLATFORM_IOS
    BTCViewController* btcController;
#endif
};
