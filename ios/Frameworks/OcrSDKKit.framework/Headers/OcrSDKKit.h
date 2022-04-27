//
//  OcrSDKKit.h
//  OcrSDKKit
//
//  Created by v_clvchen on 2020/3/24.
//  Copyright © 2020 tencent. All rights reserved.
//
#pragma once
#import "OcrSDKConfig.h"
#import "CustomConfigUI.h"
//! Project version number for OcrSDKKit.
FOUNDATION_EXPORT double OcrSDKKitVersionNumber;

//! Project version string for OcrSDKKit.
FOUNDATION_EXPORT const unsigned char OcrSDKKitVersionString[];
//OcrSDKKit @interface 对外接口
@interface OcrSDKKit : NSObject

///SDKKit处理成功回调接口
///@param resultInfo 会根据不同的工作模式返回对应下的成功信息（一般都是网络回包json字段）
///@param reserved 预留位，暂不使用
typedef void (^OcrSDKKitProcessSucceedBlock)(id _Nonnull resultInfo, UIImage * _Nullable resultImage,id _Nonnull reserved);

/// SDKKIt处理失败回调接口
/// @param error 处理过程中触发的异常错误
/// @param reserved 预留位，暂不使用
typedef void (^OcrSDKKitProcessFailedBlock)(NSError *_Nonnull error, id _Nullable reserved);

/// 获取SDK实例
+ (nonnull instancetype)sharedInstance;

/// 清理SDK资源
+ (void)clearInstance DEPRECATED_MSG_ATTRIBUTE("Please use [- (void)clearInstance]");

- (void)clearInstance;

/// 获取SDK版本信息
- (NSString *_Nonnull)getVersion;

/// SDKKIt 加载OCR配置信息
/// @param secretId  Secret id
/// @param secretKey Secret key
/// @param ocrSDKConfig ocr 配置类
- (int)loadSDKConfigWithSecretId:(NSString *_Nullable)secretId
                   withSecretKey:(NSString *_Nullable)secretKey
                      withConfig:(OcrSDKConfig *_Nullable)ocrSDKConfig;

/// 启动SDK模块，运行带有UI界面的功能识别模块
/// @param ocrType  识别模式
/// @param ocrSDKUIConfig ocrUI 配置类
/// @param onProcessSucceed  成功回调block
/// @param onProcessFailed 失败回调block
- (void)startProcessOcr:(int)ocrType
        withSDKUIConfig:(CustomConfigUI *_Nullable)ocrSDKUIConfig
withProcessSucceedBlock:(OcrSDKKitProcessSucceedBlock _Nonnull)onProcessSucceed
 withProcessFailedBlock:(OcrSDKKitProcessFailedBlock _Nonnull)onProcessFailed;


/// @param tmpSecretId 临时SecretId
/// @param tmpSecretKey 临时密钥信息
/// @param token 临时兑换token

- (void)updateFederationToken:(NSString *_Nonnull)tmpSecretId
            withTempSecretKey:(NSString *_Nullable)tmpSecretKey
                    withToken:(NSString *_Nonnull)token;

/////无法使用init new创建对象
//- (instancetype _Nonnull)init NS_UNAVAILABLE;
//
//+ (instancetype _Nonnull)new NS_UNAVAILABLE;
@end

