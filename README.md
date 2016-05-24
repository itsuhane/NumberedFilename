# NumberedFilename

从前，有一些图像处理的内部项目，需要读取一些图像序列，比如：
```
C:\somepath\somefile0000.png
C:\somepath\somefile0002.png
C:\somepath\somefile0004.png
...
C:\somepath\somefile0166.png
```
于是，他们就采用了这样的方式来描述这样的序列：
```
FirstImage: C:\somepath\somefile0000.png
Start: 0
End: 166
Step: 2
```
后来，出现了一个奇葩的序列，第一个文件编号不是0：
```
C:\somepath\somefile004.png
C:\somepath\somefile006
...
C:\somepath\somefile102.png
```
他们是这么表示这个序列的：
```
FirstImage: C:\somepath\somefile004.png
Start: 0
End: 98
Step: 2
```

又后来，有个智障程序员，他需要对接这些项目。
他首先遇到了自己不会数数的问题：

* 额如果说第一个文件是 0013 ，最后一个文件是 0247 ，然后我要写这样的配置，Start 是 0，End 是 247-13=234 还是 247-13+1=235 ？
* 额这个 End 到底是开区间还是闭区间？
* 额如果有 Step ，End 必须是个符合 Step 的编号么？

然后他又遇到了格式上的问题：

* 额如果配置里只有四位数，计数时候却跑到了五位，是截断呢还是强行多一位？

为了解决这些疑惑，他去找来了parser的代码，结果看到了类似这样的代码：
```
if(numlen==4) {
  if (number<10) {
    filename = prefix + "000" + NumberToString(number) + extension;
  } else if (number<100) {
    filename = prefix + "00" + NumberToString(number) + extension;
  } else if (number<1000) {
    filename = prefix + "0" + NumberToString(number) + extension;
  } else {
    filename = prefix + NumberToString(number) + extension; // 哦按照这里，超过位数就强行加位
  }
}
```

于是他决定无视 parser ，自己写一个，并且……

## TMD 就不会用 `FileNamePattern: "C:\\somepath\\somefile%04d.png"` 么！！！读个配置还要写个parser，这是嫌bug还不够多么？？！MDZZ
