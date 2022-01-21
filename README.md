## Recovery Device Tree for the Samsung Galaxy A10 (Exynos)

## How-to compile it:

```sh
. build/envsetup.sh
lunch omni_a10-eng
make recoveryimage -j$(nproc --all)
```
