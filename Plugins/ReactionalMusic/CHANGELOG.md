
# Changelog

## [1.0.0] - 2024-11-20
* Subsystem implementation, enabling easier access to all features.
* Unified project-wide plugin settings in 'Project Settings > Reactional Music'.
* Improved error handling and logging though all BP nodes and functions.
* Extended node tooltips to include parameter info.
* Added API functions:
  * Load Track
  * Load Theme
  * Load Playlist
  * Load Section
  * Playlist Fade
  * Theme Fade
  * Set Theme
  * Unset Theme
  * Get Theme
  * Set Track
  * Unset Track
  * Get Track
  * Schedule Audio
  * Duck Music
  * Wait For Next Beat (latent node)
  * Subscribe to Quantization Event
* Removed 'Set Sample Rate' and 'Set Buffer Size' nodes, superseded by the 'Init Audio' node where both values can be set.
* 'Get Tempo BPM' renamed to 'Get BPM'.
* Getter BP nodes converted to pure (without execution pins).
* EReactionalQuantizationValue enum extended with dotted and triplet quantized values.
* Audio component responsible for playback no longer gets flushed/destroyed on world transition.
* Added editor widget which enables easier control of playback and any theme controls in the editor.
* Enabled loading bundles at project startup in 'Project Settings > Reactional Music'
* Bugfix: Fade in/out logic.
* Bugfix: Sample rate did not get set properly in some cases.
* Bugfix: Crash caused by LoadBundles when loading async while running on a dedicated thread.

Some changes were made from the beta to this release:
Instance Manager Actor is no longer in use. Settings previously set on the actor can now be set in 'Project Settings > Reactional Music'. Migration should in most cases only require breaking the link to the Instance Manager Actor for any node and removing any leftover object references. For event bindings the target should now be the subsystem node (an example blueprint called 'BP_ReactionalBasicPlayback' is packaged with the plugin).