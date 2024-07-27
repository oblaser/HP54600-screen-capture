# SDKs as Git submodules

## Adding a submodule
https://git-scm.com/book/en/v2/Git-Tools-Submodules#_starting_submodules

```sh
$ git submodule add https://github.com/oblaser/omw.git sdk/omw
```



## Cloning the repo
https://git-scm.com/book/en/v2/Git-Tools-Submodules#_cloning_submodules

```
$ git clone --recurse-submodules <clone-URL>
```

Or:
```
$ git clone <clone-URL>
$ cd <repo>
$ git submodule init
$ git submodule update
```
