{
  "variables": {
    "libquickjs_path": "$$LIBQUICKJS_PATH"
  },
  "targets": [
    {
      "target_name": "ast-fusion",
      "sources": [
        "src/my_quickjs_addon.c",
        # "src/quickjs/*.c"
      ],
      "include_dirs": [
        "include",
      ],
      "libraries": [
        "-L<(libquickjs_path)",
        "-lquickjs",
        "-lm"
      ]
    }
  ]
}

# node-gyp build LIBQUICKJS_PATH=~/Documents/path/to/lib