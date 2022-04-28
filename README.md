# tx_ocr

腾讯云ocr插件

## Getting Started

```
android端要做的事

OcrSDKv1.0.8-release.aar包放在android/app/libs/下

在android/app/build.gradle中的dependencies里面添加
implementation(name: 'OcrSDKv1.0.8-release', ext: 'aar')

在android/app/src/main/res/values/styles.xml中添加（可能有其他作适配的values-xxx/style.xml，需要的话一并加进去）
加这个是因为aar里面windowNoTitle没有android:前缀而报错
<style name="txy_full_screen_no_title" parent="@android:style/Theme.Light.NoTitleBar">
    <item name="android:windowNoTitle">true</item>
    <item name="android:windowFullscreen">true</item>
</style>

混淆配置
#保留自定义的 OcrSDKKit 类和类成员不被混淆
-keep class com.tencent.ocr.sdk.** {*;}

#第三方 jar 包不被混淆
-keep class com.tencent.youtu.** {*;}

ios端要做的事
Build Phases -> Linked Binary With Libraries 中添加 libc++.tbd
info添加
    <key>NSPhotoLibraryUsageDescription</key>
	<string>OCR识别需要您开启相册权限，浏览您的照片</string>
	<key>NSCameraUsageDescription</key>
	<string>OCR识别需要开启您的摄像头权限，用于识别</string>
AppDelegate.h 中添加 @property (nonatomic, strong) UIWindow * window;

ios常⻅错误
1. 当提示requsetConfigDict is nil，检查下是不是在进入SDK时，执行了[OcrSDKKit cleanInstance]把秘钥和 配置设置清除了.
2. SDK⻚面依托于UIWindow，所以需要在AppDelegate.h 中添加 @property (nonatomic, strong) UIWindow * window;
3. 当出现进入SDK黑屏，添加设置Other Linker Flags添加 -ObjC。打印日志Application tried to push a nil view controller on target....，原因是self.storyboard等于 nil，可以参考demo，在调用SDK⻚面的 ViewController手动加载xib⻚面，然后调用SDK进入识别⻚面。

使用
TxOcr.setup(secretId: 'SecretId', secretKey: 'SecretKey'); // 初始化
TxOcr.startOcr(ocrType: OcrType.DriverLicenseOCR_FRONT, isLandscape: false); // 启动ocr
TxOcr.updateFederationToken(tmpSecretId, tmpSecretKey, token); // 更新临时密钥
TxOcr.dispose(); // 释放资源
```

