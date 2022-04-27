package com.xuanhai.ocr.tx_ocr;

import android.app.Activity;
import android.util.Log;

import androidx.annotation.NonNull;

import com.tencent.ocr.sdk.common.CustomConfigUi;
import com.tencent.ocr.sdk.common.ISDKKitResultListener;
import com.tencent.ocr.sdk.common.ISdkOcrEntityResultListener;
import com.tencent.ocr.sdk.common.OcrModeType;
import com.tencent.ocr.sdk.common.OcrSDKConfig;
import com.tencent.ocr.sdk.common.OcrSDKKit;
import com.tencent.ocr.sdk.common.OcrType;
import com.tencent.ocr.sdk.entity.IdCardOcrResult;

import java.util.HashMap;
import java.util.Map;

import io.flutter.embedding.engine.plugins.FlutterPlugin;
import io.flutter.embedding.engine.plugins.activity.ActivityAware;
import io.flutter.embedding.engine.plugins.activity.ActivityPluginBinding;
import io.flutter.plugin.common.MethodCall;
import io.flutter.plugin.common.MethodChannel;
import io.flutter.plugin.common.MethodChannel.MethodCallHandler;
import io.flutter.plugin.common.MethodChannel.Result;

/** TxOcrPlugin */
public class TxOcrPlugin implements FlutterPlugin, MethodCallHandler, ActivityAware {
  /// The MethodChannel that will the communication between Flutter and native Android
  ///
  /// This local reference serves to register the plugin with the Flutter Engine and unregister it
  /// when the Flutter Engine is detached from the Activity
  private MethodChannel channel;
  private FlutterPluginBinding flutterPluginBinding;
  private Activity activity;
  private boolean initSDK;
  private static final String TAG = "TxOcrPlugin";
  private final HashMap<Integer, OcrType> ocrTypeIntMap = new HashMap(){{
    put(0, OcrType.IDCardOCR_FRONT);
    put(1, OcrType.IDCardOCR_BACK);
    put(2, OcrType.BankCardOCR);
    put(3, OcrType.BusinessCardOCR);
    put(5, OcrType.LicensePlateOCR);
    put(6, OcrType.VinOCR);
    put(7, OcrType.VehicleLicenseOCR_FRONT);
    put(8, OcrType.VehicleLicenseOCR_BACK);
    put(9, OcrType.DriverLicenseOCR_FRONT);
    put(10, OcrType.DriverLicenseOCR_BACK);
  }};

  @Override
  public void onAttachedToEngine(@NonNull FlutterPluginBinding flutterPluginBinding) {
    this.flutterPluginBinding = flutterPluginBinding;
    channel = new MethodChannel(flutterPluginBinding.getBinaryMessenger(), "tx_ocr");
    channel.setMethodCallHandler(this);
  }

  @Override
  public void onMethodCall(@NonNull MethodCall call, @NonNull Result result) {
    if (call.method.equals("setup")) {
      if (initSDK) {
        result.error("1002", "不可重复初始化", null);
        return;
      }

      // 启动参数配置
      OcrModeType modeType = OcrModeType.OCR_DETECT_AUTO_MANUAL; // 设置默认的业务识别模式自动 + 手动步骤模式
      OcrType ocrType = OcrType.VehicleLicenseOCR_FRONT; // 设置默认的业务识别，银行卡
      OcrSDKConfig configBuilder = OcrSDKConfig.newBuilder(call.argument("secretId"), call.argument("secretKey"), call.argument("tempToken"))
              .ocrType(ocrType)
              .setModeType(modeType)
              .build();
      // 初始化 SDK
      OcrSDKKit.getInstance().initWithConfig(flutterPluginBinding.getApplicationContext(), configBuilder);
      initSDK = true;
      result.success("SDK初始化完成 " + OcrSDKKit.getInstance().getVersion());
    } else if (call.method.equals("dispose")) {
      OcrSDKKit.getInstance().release();
      result.success("OCR资源已释放");
    } else if(call.method.equals("updateFederationToken")) {
      OcrSDKKit.getInstance().updateFederationToken(call.argument("tmpSecretId"),call.argument("tmpSecretKey"),call.argument("token"));
      result.success("OCR临时密钥已更新");
    } else if (call.method.equals("startOcr")) {
      if (!initSDK) {
        result.error("1001", "SDK未初始化",null);
        return;
      }
      CustomConfigUi customConfigUi = new CustomConfigUi();
      if (call.hasArgument("isLandscape")) {
        customConfigUi.isLandscape = call.argument("isLandscape");
      }
      customConfigUi.setTitleBarText(call.argument("title"));
      customConfigUi.setTitleColor(0xFF006EFF);
      // 启动 ocr 识别，识别类型为身份证正面
      OcrSDKKit.getInstance().startProcessOcr(activity, ocrTypeIntMap.get(call.argument("ocrType")), customConfigUi, new ISDKKitResultListener() {
        @Override
        public void onProcessSucceed(String response, String srcBase64Image, String requestId) {
          result.success(response);
        }

        @Override
        public void onProcessFailed(String errorCode, String message, String requestId) {
          result.error("1003", errorCode + " -> " + requestId + " -> " + message, null);
        }
      });
    } else {
      result.notImplemented();
    }
  }

  @Override
  public void onDetachedFromEngine(@NonNull FlutterPluginBinding binding) {
    channel.setMethodCallHandler(null);
  }


  @Override
  public void onAttachedToActivity(ActivityPluginBinding activityPluginBinding) {
    activity = activityPluginBinding.getActivity();
  }

  @Override
  public void onDetachedFromActivityForConfigChanges() {

  }

  @Override
  public void onReattachedToActivityForConfigChanges(ActivityPluginBinding activityPluginBinding) {
  }

  @Override
  public void onDetachedFromActivity() {

  }
}
