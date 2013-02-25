#
# Copyright (C) 2012 The CyanogenMod Project
# Copyright (C) 2012 The Carbon Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# name
PRODUCT_RELEASE_NAME := d710

# device
$(call inherit-product-if-exists, device/samsung/d710/full_d710.mk)

# cdma
$(call inherit-product, vendor/carbon/config/common_cdma.mk)

# phone
$(call inherit-product, vendor/carbon/config/common_phone.mk)

# Bootanimation
TARGET_SCREEN_HEIGHT := 800
TARGET_SCREEN_WIDTH := 480

# products
PRODUCT_NAME := carbon_d710
PRODUCT_DEVICE := d710
PRODUCT_BRAND := Samsung
PRODUCT_MANUFACTURER := samsung
PRODUCT_MODEL := SPH-D710
PRODUCT_PROPERTY_OVERRIDES += ro.buildzipid=carbon.d710.$(shell date +%m%d%y).$(shell date +%H%M%S)

#Set build fingerprint
PRODUCT_BUILD_PROP_OVERRIDES += PRODUCT_NAME=SPH-D710 TARGET_DEVICE=SPH-D710 BUILD_FINGERPRINT=samsung/SPH-D710/SPH-D710:4.1.2/JZO54K/FL16:user/release-keys PRIVATE_BUILD_DESC="SPH-D710-user 4.1.2 JZ054K FL16 release-keys"
