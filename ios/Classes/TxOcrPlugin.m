#import "TxOcrPlugin.h"
#import <OcrSDKKit/OcrSDKKit.h>
#import <OcrSDKKit/OcrSDKConfig.h>

@implementation TxOcrPlugin
{
    bool initSDK;
}
+ (void)registerWithRegistrar:(NSObject<FlutterPluginRegistrar>*)registrar {
  FlutterMethodChannel* channel = [FlutterMethodChannel
      methodChannelWithName:@"tx_ocr"
            binaryMessenger:[registrar messenger]];
  TxOcrPlugin* instance = [[TxOcrPlugin alloc] init];
  [registrar addMethodCallDelegate:instance channel:channel];
}

- (void)handleMethodCall:(FlutterMethodCall*)call result:(FlutterResult)result {
  if ([@"setup" isEqualToString:call.method]) {
      NSLog(@"initSDK = %d",initSDK);
      if (initSDK) {
          result([FlutterError errorWithCode:@"1002" message:@"不可重复初始化 " details:nil]);
          return;
      }
//
      /*！
       * OCR 配置类：
       * ocrModeType: 检测类型 OCR_DETECT_MANUAL 手动拍摄； OCR_DETECT_AUTO_MANUAL 自动识别卡片
       */
      OcrSDKConfig *ocrSDKConfig = [[OcrSDKConfig alloc] init];
      ocrSDKConfig.ocrModeType = OCR_DETECT_AUTO_MANUAL;
      /// SDKKIt 加载 OCR 配置信息
      int res = [[OcrSDKKit sharedInstance] loadSDKConfigWithSecretId:call.arguments[@"secretId"] withSecretKey:call.arguments[@"secretKey"] withConfig:ocrSDKConfig];
      initSDK = 1;
      result(@"SDK初始化完成");
  } else if([@"dispose" isEqualToString:call.method]) {
      [[OcrSDKKit sharedInstance] clearInstance];
      result(@"OCR资源已释放");
  } else if([@"updateFederationToken" isEqualToString:call.method]) {
      [[OcrSDKKit sharedInstance] updateFederationToken:call.arguments[@"tmpSecretId"] withTempSecretKey:call.arguments[@"tmpSecretKey"] withToken:call.arguments[@"token"]];
      result(@"OCR临时密钥已更新");
  } else if([@"startOcr" isEqualToString:call.method]) {
      if (!initSDK) {
          result([FlutterError errorWithCode:@"1001" message:@"SDK未初始化 " details:nil]);
          return;
          BankCardOCR
      }
      NSString *ocrType = [NSString stringWithFormat:@"%@",call.arguments[@"ocrType"]];
     /*!
     * OCR UI配置类:
     */
      CustomConfigUI *customConfigUI = [[CustomConfigUI alloc] init];
      customConfigUI.remindConfirmColor = [UIColor blueColor];
      customConfigUI.isHorizontal = !call.arguments[@"isLandscape"];
      
     /// 启动SDK模块，运行带有UI界面的功能识别模块
     /// @param OcrType 识别模式
     /// @param customConfigUI UI配置对象
     /// @param onProcessSucceed 成功回调block
     /// @param onProcessFailed 失败回调block
      [[OcrSDKKit sharedInstance] startProcessOcr:[ocrType intValue] withSDKUIConfig:customConfigUI withProcessSucceedBlock:^(id  _Nonnull resultInfo,
     UIImage *resultImage, id  _Nonnull reserved) {
          result(resultInfo);
     ///resultInfo 识别成功信息(json)
     ///resultImage 识别成功后截取的图片
     } withProcessFailedBlock:^(NSError * _Nonnull error, id _Nullable reserved) {
     ///error 错误信息
     ///reserved 一般会回传requestid，定位错误
         result([FlutterError errorWithCode:@"1003" message:[@"" stringByAppendingFormat: @"%@", error] details:nil]);
     }];
  } else {
    result(FlutterMethodNotImplemented);
  }
}

@end
