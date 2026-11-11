# Vehicle First Person: behavior and implementation

Describes the exported implementation **0.1.0**. The linked source and metadata define this version; gameplay qualification is a separate requirement.

## Behavior

Alt+V toggles the native seatedFirstPerson flag while mounted and starts the normal camera blend. The feature uses the existing game camera rather than replacing the vehicle physics or adding a detached view. It roots the active walker and captures its previous seated view preference before applying the temporary override.

## State and lifecycle

The override is session-local. Toggling off, changing vehicle, focus/UI loss or leaving the world restores the captured flag through the camera restoration path. Saved vehicle identity and loadout are not rewritten.

## Integration and configuration

No additional feature-mod runtime dependency is declared. Included shared headers are source reuse, not extra DLL dependencies.

The [module metadata](../source/mods/vehicle-first-person/mod.json) owns the version and declared integration contract. Native modules start at `MoonLab_ModStart`. Game/Unity integrations target the pinned Steam Windows x64 IL2CPP build.

## Implementation sources

- [mod.c](../source/mods/vehicle-first-person/mod.c)
- [camera_restore.h](../source/mods/vehicle-first-person/camera_restore.h)
- [base.h](../source/mods/vehicle-first-person/base.h)

## Verification boundary

Cockpit visibility, obstruction/clipping, camera combinations and every vehicle type require rendered/gameplay checks. No new cockpit geometry, passenger camera or remote view is added.

`python3 build.py --check` verifies the exported source hashes. It does not execute the mod or qualify the behaviors above. Installation and independent build prerequisites are in the [README](../README.md).
