#
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html.
# Run `pod lib lint tx_ocr.podspec` to validate before publish  ing.
#
Pod::Spec.new do |s|
  s.name             = 'tx_ocr'
  s.version          = '0.0.1'
  s.summary          = '腾讯云ocr插件'
  s.description      = <<-DESC
腾讯云ocr插件
                       DESC
  s.homepage         = 'http://example.com'
  s.license          = { :file => '../LICENSE' }
  s.author           = { 'Your Company' => 'email@example.com' }
  s.source           = { :path => '.' }
  s.source_files = 'Classes/**/*'
  s.public_header_files = 'Classes/**/*.h'
  s.dependency 'Flutter'
  s.platform = :ios, '9.0'

  s.vendored_frameworks = 'Frameworks/*.framework'
  s.frameworks = 'Accelerate', 'CoreML'
  s.resources = 'Frameworks/*.bundle'

  # Flutter.framework does not contain a i386 slice.
  s.pod_target_xcconfig = { 'DEFINES_MODULE' => 'YES', 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'i386' }
end
