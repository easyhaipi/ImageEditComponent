# ImageEditComponent
一款基于涂图SDK和趣拍的图片视频编辑处理的demo

一、涂图SDK的手动接入使用(https://tusdk.com/docs/ios/get-started)

1、获取相册编辑结果图片

使用 TuSDK 的图片编辑组件，可以通过设置不同的属性以方便管理编辑结果及输出方式。

和相机类似，同样有三种方式获得图片的处理结果：

- 获取图片的 image 对象，此方式将不保存图片

- 获取图片的存储路径，此方式会将图片保存在相册中

- 将图片保存在临时文件中，并获取临时文件

1>、获取编辑结果的 image 对象

您需要进行如下设置：


    // 保存到系统相册
    _photoEditMultipleComponent.options.editMultipleOptions.saveToAlbum = NO;
    // 保存到临时文件
    _photoEditMultipleComponent.options.editMultipleOptions.saveToTemp = NO;







该方式将不会保存处理结果。

随后您可以在所设置的组件注释的方法中，按照提示写出回调方法将 result.image ，然后在外部使用方法接受图片的 image 对象。

2>获取编辑的照片对象的存储路径

您需要进行如下设置：


    // 保存到系统相册
    _photoEditMultipleComponent.options.editMultipleOptions.saveToAlbum = YES;
    // 保存到临时文件
    _photoEditMultipleComponent.options.editMultipleOptions.saveToTemp = NO;







该方式会将处理结果保存到相册中。

同时您也可以设置


    // 保存到系统相册的相册名称
    _photoEditMultipleComponent.options.editMultipleOptions.saveToAlbumName = @"TuSdk";







将图片保存到名称为 TuSdk 的相册中。

同时，此方法还可以使您获取到处理后的照片的其他属性，比如拍摄时间、文件长宽等，具体可以参看 ImageSqlInfo 类的API。

随后您可以在所设置的组件注释的方法中，按照提示写出回调方法将 result ，然后在外部使用方法接受图片对象。

3>获取编辑结果所在的临时文件

您需要进行如下设置：


    // 保存到系统相册
    _photoEditMultipleComponent.options.editMultipleOptions.saveToAlbum = NO;
    // 保存到临时文件
    _photoEditMultipleComponent.options.editMultipleOptions.saveToTemp = YES;







该方式将会把处理结果保存到临时文件，同时您也可以设置


    // 控制器关闭后是否自动删除临时文件
    _photoEditMultipleComponent.options.editMultipleOptions.isAutoRemoveTemp = YES;







这样在处理完成之后将会自动删除临时文件。

随后您可以在所设置的组件注释的方法中，按照提示写出回调方法将 result.imagePath ，然后在外部使用方法接受图片对象。

当上面的配置完成之后，最后不要忘记加上下面的代码打开组件：

    // 设置图片
    _photoEditMultipleComponent.inputImage = result.image;
    _photoEditMultipleComponent.inputTempFilePath = result.imagePath;
    _photoEditMultipleComponent.inputAsset = result.imageAsset;
    // 是否在组件执行完成后自动关闭组件 (默认:NO)
    _photoEditMultipleComponent.autoDismissWhenCompelted = YES;
    // 当上一个页面是NavigationController时,是否通过 pushViewController 方式打开编辑器视图 (默认：NO，默认以 presentViewController 方式打开）
    // SDK 内部组件采用了一致的界面设计，会通过 push 方式打开视图。如果用户开启了该选项，在调用时可能会遇到布局不兼容问题，请谨慎处理。
    _photoEditMultipleComponent.autoPushViewController = YES;
    [_photoEditMultipleComponent showComponent];

2、图片编辑的处理结果注意：


// 图片处理结果 TuSDKResult *result 具有三种属性，分别是 ：
        // result.image 是 UIImage 类型
        // result.imagePath 是 NSString 类型
        // result.imageAsset 是 TuSDKTSAssetInterface 类型

        // 下面以 result.image 举例如何将图片编辑结果持有并进行其他操作
        // 可在此添加自定义方法，将 result 结果传出，例如 ：  [self openEditorWithImage:result.image];
        // 并在外部使用方法接收 result 结果，例如 ： -(void)openEditorWithImage:(UIImage *)image;
        // 用户也可以在 result 结果的外部接受的方法中实现页面的跳转操作，用户可根据自身需求使用。

        // 用户在获取到 result.image 结果并跳转到其他页面进行操作的时候可能会出现无法持有对象的情况
        // 此时用户可以将 result.image 对象转换成 NSData 类型的对象，然后再进行操作，例如 ：
        // NSData *imageData = UIImageJPEGRepresentation(result.image, 1.0);
        // ViewController *viewController = [[ViewController alloc]init];
        // [self.controller pushViewController:viewController animated:YES];
        // viewController.currentImage = [UIImage imageWithData:imageData];

        // 获取 result 对象的不同属性，需要对 option 选项中的保存到相册和保存到临时文件相关项进行设置。
        //







3、

相机拍照选项

- 设置后置摄像头优先启动，默认是后置摄像头启动


    opt.cameraPostion = [AVCaptureDevice firstBackCameraPosition];







- 设置前置摄像头优先启动


    opt.cameraPostion = [AVCaptureDevice firstFrontCameraPosition];







- 设置前置摄像头拍照水平镜像，设置为 NO ，拍摄的照片会出现左右镜像变化


    opt.disableMirrorFrontFacing = YES;







- 拍照分辨率，默认设置最高，修改设置可查阅AVCaptureSession文档选择合适的模式


    opt.sessionPreset = AVCaptureSessionPresetHigh;







- 照片输出压缩率,设置范围压缩率 0-1 如果设置为0 将保存为PNG格式，默认设置是 0.95。


    opt.outputCompress = 0.95f;







- 视频覆盖区域颜色,默认设置是 [UIColor clearColor] ，更改设置需要将颜色的代码部分转化为十六进制转的颜色对象，十六进制字符串，例如 @"#FF5534"


    opt.regionViewColor = [UIColor lsqClorWithHex:@"#403e43"];







- 照片的输出图片大小，可以控制输出照片的尺寸，设置 ratioType 功能配置项将会失效。


    opt.outputSize = CGSizeMake(1440, 1920);







- 闪光灯关闭模式，默认是设置关闭


  opt.cameraDefaultFlashMode = AVCaptureFlashModeOff;







- 闪光灯开启模式，设置为开启模式，启动相机摄像头，闪光灯开启


  opt.cameraDefaultFlashMode = AVCaptureFlashModeOn;







- 闪光灯自动模式，闪光灯会根据光线强度，自动开启或关闭


  opt.cameraDefaultFlashMode = AVCaptureFlashModeAuto;







- 相机视图显示比例设置，可以直接设置比例，默认是 0 显示全屏，设置范围 0-1 ， 0 <= mRegionRatio


    opt.cameraViewRatio = 0.75f







- 相机视图显示比例类型设置，默认设置是 lsqRatioDefault, 如果设置cameraViewRatio > 0, 将忽略ratioType


    // 默认比例
    lsqRatioDefault = lsqRatioOrgin | lsqRatio_1_1 | lsqRatio_2_3 | lsqRatio_3_4 | lsqRatio_9_16；
    // 全部比例
    lsqRatioAll = lsqRatioOrgin | lsqRatio_1_1 | lsqRatio_2_3 | lsqRatio_3_4 | lsqRatio_9_16 | lsqRatio_3_2 | lsqRatio_4_3 | lsqRatio_16_9;
    // 默认设置
    opt.ratioType = lsqRatioDefault;
    // 自定义设置 (不支持排序)
    opt.ratioType = lsqRatio_9_16 | lsqRatio_3_2 | lsqRatio_4_3 | lsqRatio_16_9;









- 相机网格辅助线，默认设置是 false 表示关闭辅助线，可设置启动相机时开启辅助线


    opt.displayGuideLine = false;







- 长按设置，默认是 NO 表示关闭，设置开启后长按可以拍摄


    opt.enableLongTouchCapture = YES;







- 长按延时设置，默认设置为 1.2秒，可以手动更改


    opt.longTouchDelay = 1.2;







- 持续自动对焦，默认设置是 NO 表示关闭，开启后每间隔固定时间会自动进行对焦


    opt.disableContinueFoucs = YES;







- 自动聚焦延时，默认设置 5秒，可以更改时间，每间隔 5 秒进行相机进行对焦


    opt.autoFoucsDelay = 5;







4、相册按钮的点击事件

- 显示相册入口,默认是不显示的，设置为显示时，需要自己处理点击事件


    opt.displayAlbumPoster = YES;







- 实现相册入口按钮点击的代理方法

/**
 *  请求从相机界面跳转至相册
 *
 *  @param controller 默认相机视图控制器
 */
- (void)onTuSDKAlbumDemand:(TuSDKPFCameraViewController *)controller;
{
     // 处理相册按钮的点击事件
}

5、

获取相机的拍照结果

使用 TuSDK 提供的相机执行拍摄动作之后，用户可以通过以下三种不同的方式获得拍摄图片：

- 获取图片的 image 对象，此方式将不保存图片

- 获取图片的存储路径，此方式会将图片保存在相册中

- 将图片保存在临时文件中，并获取临时文件

处理拍照结果的配置项

- 保存到系统相册，默认是不保存, 当设置为 YES 时, 可以得到照片对象 TuSDKResult.asset


    opt.saveToAlbum = YES;







- 保存到临时文件,默认是不保存, 当设置为 YES 时, 可获取图片保存的临时文件路径 TuSDKResult.tmpFile


    opt.saveToTemp = NO;







- 保存到系统相册的相册名称，可根据需求改变相册名称


    opt.saveToAlbumName = @"TuSdk";







获取图片的 image 对象

需要设置 TuSDKPFCameraOptions 类的下面几个属性：


    TuSDKPFCameraOptions *opt = [TuSDKPFCameraOptions build];

    // 保存到系统相册 (默认不保存, 当设置为YES时, TuSDKResult.asset)
    opt.saveToAlbum = NO;

    // 保存到临时文件 (默认不保存, 当设置为YES时, TuSDKResult.tmpFile)
    opt.saveToTemp = NO;







该方式将不会保存拍照结果，如需保存须在获得图片之后自行处理。

随后您可以在


- (void)onTuSDKPFCamera:(TuSDKPFCameraViewController *)controller captureResult:(TuSDKResult *)result;







获取图片的 image 对象即 result.image。

获取图片的存储路径

需要设置 TuSDKPFCameraOptions 类的下面几个属性：


    TuSDKPFCameraOptions *opt = [TuSDKPFCameraOptions build];

    // 保存到系统相册 (默认不保存, 当设置为YES时, TuSDKResult.asset)
    opt.saveToAlbum = YES;

    // 保存到临时文件 (默认不保存, 当设置为YES时, TuSDKResult.tmpFile)
    opt.saveToTemp = NO;







该方式会将拍摄结果保存在相册中，同时您也可以通过设置


    // 保存到系统相册的相册名称
    opt.saveToAlbumName = @"TuSdk";







将图片保存到名称为 TuSdk 的相册中。

随后可以在


- (void)onTuSDKPFCamera:(TuSDKPFCameraViewController *)controller captureResult:(TuSDKResult *)result;







获取照片的路径。

获取图片所在的临时文件 result.imagePath

需要设置 TuSDKPFCameraOptions 类的下面几个属性：


    TuSDKPFCameraOptions *opt = [TuSDKPFCameraOptions build];

    // 保存到系统相册 (默认不保存, 当设置为YES时, TuSDKResult.asset)
    opt.saveToAlbum = NO;

    // 保存到临时文件 (默认不保存, 当设置为YES时, TuSDKResult.tmpFile)
    opt.saveToTemp = YES;







该方式将会把拍摄结果保存在临时文件中，在处理完成之后将会清理原始图片。

随后可以在


- (void)onTuSDKPFCamera:(TuSDKPFCameraViewController *)controller captureResult:(TuSDKResult *)result;







获取临时文件。

二、趣拍SDK的手动接入使用(http://docs.qupaicloud.com/119.html)

跟着文档就可以搭建自己的应用服务
