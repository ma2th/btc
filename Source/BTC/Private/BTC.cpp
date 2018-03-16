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

#include "BTC.h"
#include "BTCInputDevice.h"

class FBTCDeviceModule : public IBTCDeviceModule
{
public:
    virtual void StartupModule() override;
    
    virtual void ShutdownModule() override;
    
    virtual TSharedPtr<class IInputDevice> CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& MessageHandler);
    
    virtual void Activate() override;
    virtual void Deactivate() override;
    
private:
    FThreadSafeBool Active = true;
    TSharedPtr<FBTCInputDevice> Device;
};

IMPLEMENT_MODULE(FBTCDeviceModule, BTC)

void FBTCDeviceModule::StartupModule()
{
    IModularFeatures::Get().RegisterModularFeature(IInputDeviceModule::GetModularFeatureName(), this);
}

void FBTCDeviceModule::ShutdownModule()
{
    IModularFeatures::Get().UnregisterModularFeature(IInputDeviceModule::GetModularFeatureName(), this);
}

TSharedPtr<class IInputDevice> FBTCDeviceModule::CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& MessageHandler)
{
    Device = MakeShareable(new FBTCInputDevice(MessageHandler, Active));
    return StaticCastSharedPtr<IInputDevice>(Device);
}

void FBTCDeviceModule::Activate()
{
    Active = true;
    
    if (Device.IsValid())
    {
        Device->Activate();
    }
}

void FBTCDeviceModule::Deactivate()
{
    Active = false;
    
    if (Device.IsValid())
    {
        Device->Deactivate();
    }
}
