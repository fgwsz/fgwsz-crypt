# fgwsz-package

`fgwsz-package`是一个进行打包和解包的工具,
用它打包的包内容使用随机编码混淆.  

```txt
fgwsz-package归档一个或多个(文件/目录)的包标准:
    包的二进制的文件结构如下:
        [file item 1]...[file item N]
    每个文件的二进制信息[file item]的文件结构是[A|B|C|D]:
        A部分是[relative path bytes(8字节)]
        B部分是[relative path]
        C部分是[content bytes(8字节)]
        D部分是[content(binary)]
```

`fgwsz-package`打包生成的包文件后缀名可以是任意名称.

为了避免陷入要使用某个具有神秘后缀名的包,却不知道该用何种软件打开它的困境.  

在此约定,使用`fgwsz-package`打包生成的包文件统一使用`.fgwsz`作为后缀名.

`fgwsz-package`的命令行使用方式如下:  

```txt
Usages:
    Pack  : -c <output-package-path> <input-path-1> [<input-path-2> ...]
    Unpack: -x <input-package-path> <output-directory-path>
    List  : -l <input-package-path>
Examples:
    Pack a file and directory: -c 0.fgwsz README.md source
    Unpack                   : -x 0.fgwsz output
    List package contents    : -l 0.fgwsz
```

一个特性(不是漏洞):

打包模式下输入的目录路径尾部是否有`/`,会影响打包时的处理逻辑:

&ensp;&ensp;&ensp;&ensp;输入的目录路径尾部不含有`/`,
会匹配到整个目录,包含目录自身.

&ensp;&ensp;&ensp;&ensp;输入的目录路径尾部含有`/`,
会匹配到整个目录下的所有子目录/文件,不包含目录自身.

```txt
当前工作目录结构如下:

    ./
    |
    +----source/
    |    |
    |    |----main.cpp
    |    |----hello_world.h
    |    +----hello_world.cpp
    |
    +----README.md

情况一:使用目录路径(目录名后无'/')打包解包

    fgwsz-package -c 0.fgwsz README.md source
    fgwsz-package -x 0.fgwsz out

    输出路径out的目录结构如下:

        out/
        |
        +----source/
        |    |
        |    |----main.cpp
        |    |----hello_world.h
        |    +----hello_world.cpp
        |
        +----README.md

情况二:使用目录路径(目录名后有'/')打包解包

    fgwsz-package -c 0.fgwsz README.md source/
    fgwsz-package -x 0.fgwsz out

    输出路径out的目录结构如下:

        out/
        |
        |----main.cpp
        |----hello_world.h
        |----hello_world.cpp
        +----README.md
```

编码问题:

```txt
linux操作系统默认使用utf-8编码,无需设置.

windows操作系统请先设置全局编码为utf-8编码,设置方式如下:
    区域设置->勾选"Beta:使用 Unicode UTF-8 提供全球语言支持"选项
    由此,可以避免在windows系统使用本软件的时候出现编码错误.
```
