// File generated by FlutterFire CLI.
// ignore_for_file: lines_longer_than_80_chars, avoid_classes_with_only_static_members
import 'package:firebase_core/firebase_core.dart' show FirebaseOptions;
import 'package:flutter/foundation.dart'
    show defaultTargetPlatform, kIsWeb, TargetPlatform;

/// Default [FirebaseOptions] for use with your Firebase apps.
///
/// Example:
/// ```dart
/// import 'firebase_options.dart';
/// // ...
/// await Firebase.initializeApp(
///   options: DefaultFirebaseOptions.currentPlatform,
/// );
/// ```
class DefaultFirebaseOptions {
  static FirebaseOptions get currentPlatform {
    if (kIsWeb) {
      return web;
    }
    switch (defaultTargetPlatform) {
      case TargetPlatform.android:
        return android;
      case TargetPlatform.iOS:
        return ios;
      case TargetPlatform.macOS:
        return macos;
      case TargetPlatform.windows:
        throw UnsupportedError(
          'DefaultFirebaseOptions have not been configured for windows - '
          'you can reconfigure this by running the FlutterFire CLI again.',
        );
      case TargetPlatform.linux:
        throw UnsupportedError(
          'DefaultFirebaseOptions have not been configured for linux - '
          'you can reconfigure this by running the FlutterFire CLI again.',
        );
      default:
        throw UnsupportedError(
          'DefaultFirebaseOptions are not supported for this platform.',
        );
    }
  }

  static const FirebaseOptions web = FirebaseOptions(
    apiKey: 'AIzaSyB6gXcrJJTvQLTfifbLMIdo6F2Y6MvLKqs',
    appId: '1:804202872073:web:324a2213ec7038390de7d8',
    messagingSenderId: '804202872073',
    projectId: 'session5-179dc',
    authDomain: 'session5-179dc.firebaseapp.com',
    databaseURL: 'https://session5-179dc-default-rtdb.firebaseio.com',
    storageBucket: 'session5-179dc.appspot.com',
    measurementId: 'G-YT9T18V4W7',
  );

  static const FirebaseOptions android = FirebaseOptions(
    apiKey: 'AIzaSyABvAzwJzCrhdbAM9YEUiNqb_fTL-NGOm0',
    appId: '1:804202872073:android:e57633a878fb63540de7d8',
    messagingSenderId: '804202872073',
    projectId: 'session5-179dc',
    databaseURL: 'https://session5-179dc-default-rtdb.firebaseio.com',
    storageBucket: 'session5-179dc.appspot.com',
  );

  static const FirebaseOptions ios = FirebaseOptions(
    apiKey: 'AIzaSyCKIkXXokU7DP9nrezCkMuhMmW5Rr3oIso',
    appId: '1:804202872073:ios:3d0204edd05051080de7d8',
    messagingSenderId: '804202872073',
    projectId: 'session5-179dc',
    databaseURL: 'https://session5-179dc-default-rtdb.firebaseio.com',
    storageBucket: 'session5-179dc.appspot.com',
    iosClientId: '804202872073-v0vqeh2vl3bi1iv14dp32rrcefrec238.apps.googleusercontent.com',
    iosBundleId: 'com.example.try1',
  );

  static const FirebaseOptions macos = FirebaseOptions(
    apiKey: 'AIzaSyCKIkXXokU7DP9nrezCkMuhMmW5Rr3oIso',
    appId: '1:804202872073:ios:fd0385f02caaf30d0de7d8',
    messagingSenderId: '804202872073',
    projectId: 'session5-179dc',
    databaseURL: 'https://session5-179dc-default-rtdb.firebaseio.com',
    storageBucket: 'session5-179dc.appspot.com',
    iosClientId: '804202872073-5sok6t6ciu0eeh523eovhaat13roa4jg.apps.googleusercontent.com',
    iosBundleId: 'com.example.try1.RunnerTests',
  );
}
