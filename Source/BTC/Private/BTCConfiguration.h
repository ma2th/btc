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

// Comment or uncomment the following lines to configure which buttons
// are considered.
//
// If your controller does not support the Bluetooth HID profile,
// comment USE_ENTER_BUTTON. Otherwise the virtual keyboard will
// appear in VR mode.
//
// If sound playback should not be affected, comment USE_SOUND_BUTTONS.

#define USE_ENTER_BUTTON
#define USE_ARROW_BUTTONS
#define USE_SOUND_BUTTONS

// Adapt the following definitions to change the mapping of physical
// buttons to UE4 events.

#include "IInputDevice.h"

namespace BTCEventMapping {
    const FGamepadKeyNames::Type LEFT = FGamepadKeyNames::DPadLeft;
    const FGamepadKeyNames::Type RIGHT = FGamepadKeyNames::DPadRight;
    const FGamepadKeyNames::Type UP = FGamepadKeyNames::DPadUp;
    const FGamepadKeyNames::Type DOWN = FGamepadKeyNames::DPadDown;
    const FGamepadKeyNames::Type ENTER = FGamepadKeyNames::RightShoulder;
    const FGamepadKeyNames::Type PLAY_PAUSE = FGamepadKeyNames::FaceButtonRight;
    const FGamepadKeyNames::Type MUTE = FGamepadKeyNames::FaceButtonLeft;
    const FGamepadKeyNames::Type VOLUME_UP = FGamepadKeyNames::FaceButtonBottom;
    const FGamepadKeyNames::Type VOLUME_DOWN = FGamepadKeyNames::FaceButtonTop;
}


