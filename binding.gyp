{
  "variables": {
    "libquickjs_path": "<!(echo \"${LIBQUICKJS_PATH}\")"
  },
  "targets": [
    {
      "target_name": "my_quickjs_addon",
      "sources": [
        "src/my_quickjs_addon.c",
        # "src/quickjs/*.c"
      ],
      "include_dirs": [
        "include",
        # "/home/asanka/Documents/my-quickjs-addon/src/quickjs"
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