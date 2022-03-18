## Ashes of War
Implements a Special Attack to weapons via an enchantment, with inspiration from Elden Ring

## Requirements
* [SKSE](http://skse.silverlock.org/)
	* Needed for the Plugin itself
* [Nemesis](https://www.nexusmods.com/skyrimspecialedition/mods/60033)
	* For the Ash of War behaviours and animations
* [Animation Motion Revolution](https://www.nexusmods.com/skyrimspecialedition/mods/50258)
	* For the Animation Motion Data
* [Dynamic Animation Replacer](https://www.nexusmods.com/skyrimspecialedition/mods/33746)
	* For conditional anims and faster caching.

	
## Development
To develop an Ash of War you must first make 3 things:
* Enchantment
	* Made for a weapon
* Power
	* Automatically given to you by the mod when equipping a weapon with your enchantment
* Magic Effect
	* This effect does 2 things;
	* 1. Decides which Ash of War animation to play via DAR
	* 2. Serves as the behaviour event trigger
	
After which is done, you place their FormIDs in the Spells folder, either in the base .toml or a custom created one for your project.

```
EffectFormID      = the Form ID of the Magic Effect, gotten with CK, zEdit, or xEdit.
EnchantmentFormID = the Form ID of the Enchantment, gotten with CK, zEdit, or xEdit.
PowerFormID       = the Form ID of the Power, gotten with CK, zEdit, or xEdit
EspName           = the name of the .esp all of these belong to
```

After that is done, you may develop any spells you wish the Ash of War to use, and begin making the actual Ash of War.

In the DynamicAnimationCasting folder, in a .toml, create an entry for your Ash of War with these settings:
```
AnimationEvent = The animation event you wish to spawn the spells on
ActorFormID    = Optional, will only allow the spells to spawn for this actor. Set to 0 or -1 to ignore.
RaceFormID     = Optional, will only allow the spells to spawn for this race. Set to 0 or -1 to ignore.
WeaponFormID   = Optional, will only allow the spells to spawn while the actor holds this weapon. Set to 0 or -1 to ignore.
EffectFormID   = Optional, will only allow the spells to spawn while the actor has this active effect. Set to 0 or -1 to ignore.
KeywordFormID  = Optional, will only allow the spells to spawn while the actor has this keyword. Set to 0 or -1 to ignore.
KeywordEspName = Optional, if the keyword is not ignored, the name of the .esp the keyword belongs to.
SpellFormIDs   = The Form IDs of the spells you want you spawn when meeting the conditions
SpellEspName   = The name of the .esp the spells belong to.
TargetCaster   = whether or not the spell targets the caster
HealthCost     = the health cost for spawning the spells.  (NOTE: Only subtracts once, NOT for each spell)
StaminaCost    = the stamina cost for spawning the spells. (NOTE: Only subtracts once, NOT for each spell)
MagickaCost    = the magicka cost for spawning the spells. (NOTE: Only subtracts once, NOT for each spell)
```

Once all is done, create a DAR setup for the animations you wish to use, with the condition HasMagicEffect(YourEffectFormID)

After this, go in-game and use your Ash of War.
