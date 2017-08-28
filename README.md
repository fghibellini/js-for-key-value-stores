
# HelloWorld example of V8 embedding with Nix

This project showcases how easy it is to laverage the power of [V8](//developers.google.com/v8/) by using the [Nix](//nixos.org/nix/) package manager.

Compare to the [V8 embedding tutorial](//github.com/v8/v8/wiki/Getting%20Started%20with%20Embedding).

## Steps

1. Get a machine with [Nix](//nixos.org/nix/) installed.
2. Clone this project and cd into its root `git clone 'https://github.com/fghibellini/v8-embedding-nixos.git' && cd ./v8-embedding-nixos`.
2. Start a nix shell environment from the project root folder `nix-shell`.
3. You're left in a shell with everything set up, just modify the source code in [src/main.cpp](./src/main.cpp) and run `make run` to see the results.
