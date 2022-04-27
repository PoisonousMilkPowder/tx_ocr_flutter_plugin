import 'dart:async';
import 'dart:convert';

import 'package:flutter/services.dart';

class TxOcr {
  static const MethodChannel _channel = MethodChannel('tx_ocr');

  static Future<String?> setup({required String secretId, required String secretKey, String? tempToken}) async {
    final String? res = await _channel.invokeMethod('setup', {
      "secretId": secretId,
      "secretKey": secretKey,
      "tempToken": tempToken,
    });
    return res;
  }

  static Future startOcr({required int ocrType, bool isLandscape = false}) async {
    try {
      // title仅android端可配置，ios端没有对应方法
      var title = OcrType.getTitleByType(ocrType);
      var res = await _channel.invokeMethod('startOcr', {"ocrType": ocrType, "isLandscape": isLandscape, "title": title});
      if (res.runtimeType == String) {
        res = json.decode(res);
      }
      return res;
    } catch (e) {
      return Future.error(e);
    }
  }

  static Future<String?> updateFederationToken(String tmpSecretId, String tmpSecretKey, String token) async {
    final String? res = await _channel.invokeMethod('updateFederationToken', {
      "tmpSecretId": tmpSecretId,
      "tmpSecretKey": tmpSecretKey,
      "token": token,
    });
    return res;
  }

  static Future<String?> dispose() async {
    final String? res = await _channel.invokeMethod('dispose');
    return res;
  }
}

class OcrType {
//      IDCardOCR_FRONT = 0,//身份证正面
//      IDCardOCR_BACK = 1,     //身份证反面
//      BankCardOCR = 2,        //银行卡识别
//      BusinessCardOCR = 3,    //名片识别
//      MLIdCardOCR = 4,        //马来西亚身份证识别
//      LicensePlateOCR = 5,    //车牌识别
//      VinOCR = 6,              // vin码识别
//      VehicleLicenseOCR_FRONT = 7, //行驶证主页
//      VehicleLicenseOCR_BACK = 8,  //行驶证副页
//      DriverLicenseOCR_FRONT = 9,  //驾驶证主页
//      DriverLicenseOCR_BACK = 10    //驾
  static const int IDCardOCR_FRONT = 0;
  static const int IDCardOCR_BACK = 1;
  static const int BankCardOCR = 2;
  static const int BusinessCardOCR = 3;
  static const int LicensePlateOCR = 5;
  static const int VinOCR = 6;
  static const int VehicleLicenseOCR_FRONT = 7;
  static const int VehicleLicenseOCR_BACK = 8;
  static const int DriverLicenseOCR_FRONT = 9;
  static const int DriverLicenseOCR_BACK = 10;

  static String getTitleByType(int type) {
    switch (type) {
      case IDCardOCR_FRONT:
      case IDCardOCR_BACK:
        return '身份证识别';
      case DriverLicenseOCR_FRONT:
      case DriverLicenseOCR_BACK:
        return '驾驶证识别';
      case VehicleLicenseOCR_FRONT:
      case VehicleLicenseOCR_BACK:
        return '行驶证识别';
      case LicensePlateOCR:
        return '车牌识别';
      case VinOCR:
        return '车辆VIN识别';
      case BusinessCardOCR:
        return '名片识别';
      case BankCardOCR:
        return '银行卡识别';
    }
    return '卡证识别';
  }
}
