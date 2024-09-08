# Vst-Plungins
- Distortion
  - Dry-wet
  - Level
  - Gain
- Reverb
  - Dry-wet
  - High
  - Low
  - Mid
- Delay
  - Delay time
- Fuzz
  - Level
  - Gain
- *Shoegaze
- *Dreampop
## Distortion
### Effect
By creating some distorted noise accompanying the dry guitar sound, the guitar voise becomes wilder than before.
### How?
- Hard-Clipping
  - Just clip the top amplitude, limit it to a single value
  - `if x > limit, then x = limit`
- Soft-Clipping
  - Using functions that make the clipping sound more gentle, e.g. a tanh(x) function
  - `if x > limit, then x = tanh(x)`
## Fuzz
Similar to distortion, need to clip the top amplitudes, but through a rather different approach.
Using the function, `f(x) = x*(abs(x)+1/abs(x)+0.5)`, it makes the upper signal similar to square-wave-like.
## Reverb
Using comb filters and all-pass filters to create a echo sound.
## Chorus
