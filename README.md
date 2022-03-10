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
	* This effect does 3 things;
	* 1. Decides which Ash of War animation to play via DAR
	* 2. Serves as the behaviour event trigger
	* 3. Is used by the Ash of War's spell calculation in damage, using magnitude
	
After which is done, you place their FormIDs in the Spells folder, either in the base .toml or a custom created one for your project.

After that is done, you may develop any spells you wish the Ash of War to use, and begin making the actual Ash of War.

In the AshesOfWar folder, in a .toml, create an entry for your Ash of War with these settings:
```
Payload = The payload string you want the spells to spawn on. (list here)
SpellFormIDs = an array of Form IDs you want the Ash of War to use.
DamageType = The Spells' damage types, 0 = Physical, 1 = Elemental
MagickaCost = Magicka Cost for the Ash of War, not the spells 
StaminaCost = Stamina Cost for ^
```

Once all is done, create a DAR setup for the animations you wish to use, with the condition HasMagicEffect(YourEffectFormID)

After this, go in-game and use your Ash of War.