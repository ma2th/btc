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
    virtual void StartupModule() override;
    
    virtual void ShutdownModule() override;
    
    virtual TSharedPtr<class IInputDevice> CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& MessageHandler);
};

IMPLEMENT_MODULE(FBTCDeviceModule, BTC)

void FBTCDeviceModule::StartupModule()
{
    UE_LOG(LogTemp, Log, TEXT("BTC plugin starting"));
    IModularFeatures::Get().RegisterModularFeature(IInputDeviceModule::GetModularFeatureName(), this);
}

void FBTCDeviceModule::ShutdownModule()
{
    UE_LOG(LogTemp, Log, TEXT("BTC plugin shutting down"));
    IModularFeatures::Get().UnregisterModularFeature(IInputDeviceModule::GetModularFeatureName(), this);
}

TSharedPtr<class IInputDevice> FBTCDeviceModule::CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& MessageHandler)
{
    UE_LOG(LogTemp, Log, TEXT("BTC plugin create input device"));
    return MakeShareable(new FBTCInputDevice(MessageHandler));
}
