with import <nixpkgs> {};

stdenv.mkDerivation {
  name = "google-projects-0.0.1";

  inherit v8;
  inherit icu;

  buildInputs = [ gcc ];

  #src = fetchgit {
  #  url = "https://chromium.googlesource.com/chromium/tools/depot_tools.git";
  #};

}
