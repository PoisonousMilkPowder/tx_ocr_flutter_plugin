//
//  OcrCommDef.h
//  OcrSDKKit
//
//  Created by v_clvchen on 2020/7/20.
//  Copyright © 2020 tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

///ocr的业务类型
NS_ASSUME_NONNULL_BEGIN
typedef NS_ENUM(int, OcrType)
{
    IDCardOCR_FRONT = 0,//身份证正面
    IDCardOCR_BACK = 1,     //身份证反面
    BankCardOCR = 2,        //银行卡识别
    BusinessCardOCR = 3,    //名片识别
    MLIdCardOCR = 4,        //马来西亚身份证识别
    LicensePlateOCR = 5,    //车牌识别
    VinOCR = 6,              // vin码识别
    VehicleLicenseOCR_FRONT = 7, //行驶证主页
    VehicleLicenseOCR_BACK = 8,  //行驶证副页
    DriverLicenseOCR_FRONT = 9,  //驾驶证主页
    DriverLicenseOCR_BACK = 10    //驾驶证副页
};
typedef NS_ENUM(int,OcrModeType){
    OCR_DETECT_MANUAL = 0, /// 手动拍摄
    OCR_DETECT_AUTO_MANUAL, /// 自动识别  tips：20s后提示 是否切换到手动拍摄
};

NS_ASSUME_NONNULL_END
