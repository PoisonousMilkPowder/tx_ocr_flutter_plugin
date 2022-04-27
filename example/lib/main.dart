import 'dart:convert';

import 'package:flutter/material.dart';
import 'package:tx_ocr/tx_ocr.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({Key? key}) : super(key: key);

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  String _platformVersion = 'Unknown';

  @override
  void initState() {
    super.initState();
  }

  @override
  void dispose() {
    TxOcr.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Plugin example app'),
        ),
        body: Column(
          children: <Widget>[
            TextButton(
                onPressed: () {
                  TxOcr.setup(secretId: 'SecretId', secretKey: 'SecretKey').then((value) => print(value));
                },
                child: Text('初始化')),
            TextButton(
                onPressed: () async {
                  try {
                    var res = await TxOcr.startOcr(ocrType: OcrType.VehicleLicenseOCR_FRONT);
                    setState(() {
                      _platformVersion = json.encode(res);
                    });
                  } catch (e) {
                    print(e);
                  }
                },
                child: Text('ocr识别')),
            Text('识别结果: $_platformVersion')
          ],
        ),
      ),
    );
  }
}
