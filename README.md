## Recovery Device Tree for the Samsung Galaxy A20 (Exynos)

## How-to compile it:

```sh
. build/envsetup.sh
lunch omni_a20-eng
make recoveryimage -j$(nproc --all)
```
