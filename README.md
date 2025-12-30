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
    Pack  : -c <output package path> <input path 1> ... <input path N>
    Unpack: -x <input package path> <output directory path>
Examples:
    Pack a file and directory: -c 0.fgwsz README.md source
    Unpack                   : -x 0.fgwsz output
```
