import 'package:first_app/sensor_screen.dart';
import 'package:flutter/material.dart';

class SignupScreen extends StatelessWidget {
  final TextEditingController emailController = TextEditingController();
  final TextEditingController passwordController = TextEditingController();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Sign Up'),
      ),
      body: Padding(
        padding: EdgeInsets.all(16.0),
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Image.asset(
              'lib/assets/images/logo2.png',
              width: 200,
              height: 200,
            ),
            TextField(
              controller: emailController,
              decoration: InputDecoration(labelText:'Email'),
            ),
            TextField(
              controller: passwordController,
              decoration: InputDecoration(labelText:'Password'),
            ),
            ElevatedButton(
              onPressed: () {
                Navigator.push(context,
                  MaterialPageRoute(builder: (context) => SensorApp()),
                );
              },
              child: Text('Sign Up'),

            ),
          ],
        ),
      ),
    );
  }
}