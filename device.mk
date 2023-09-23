LOCAL_PATH := device/samsung/a20

# Fastbootd
PRODUCT_PACKAGES += \
	fastbootd \
	android.hardware.fastboot@1.0-impl-mock \
	android.hardware.fastboot@1.0-impl-mock.recovery

# Flashlight initializer
PRODUCT_PACKAGES += init_flashlight

PRODUCT_PRODUCT_PROPERTIES += \
	ro.fastbootd.available=true
