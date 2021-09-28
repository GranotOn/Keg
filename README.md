<p align="center">
    <img alt="keg" src="./docs/_media/icon.svg" width="200" height="200">
</p>

<p align="center">
  The development repository for Keg game engine
</p>

## Getting Started

### Cloning

This repository uses github submodules as a dependency, so make you sure clone this repository recursively:

```
git clone --recurse-submodules https://github.com/OwenGranot/Keg
```

### Building

- This project currently supports premake for the build configuration.
- A `built.bat` is available for Windows users.
- The built process will output a `Keg.sln` file that you can open and run with `Visual Studio`.

### Documentation

This project currently uses a local version of `docsify` for documentation. Provided is a quick start guide to serve the documentation files:

1. Make sure you have NPM installed.
2. Install docsify globally using `npm i docsify-cli -g`
3. In the project root directory (where the `./docs` subdirctory resides) you can serve the documentation using `docsify serve ./docs`
