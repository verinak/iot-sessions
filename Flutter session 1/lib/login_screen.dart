import 'package:first_app/sensor_screen.dart';
import 'package:flutter/material.dart';

class LoginScreen extends StatelessWidget {
  final TextEditingController emailController = TextEditingController();
  final TextEditingController passwordController = TextEditingController();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Log In'),
      ),
      body: Padding(
        padding: EdgeInsets.all(16.0),
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Image.asset(
              'lib/assets/images/logo1.png',
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
                String email = emailController.text;
                String password = passwordController.text;
                // Add your login logic here
                Navigator.push(context,
                  MaterialPageRoute(builder: (context) => SensorApp()),
                );
              },
              child: Text('Log In'),
            ),
          ],
        ),
      ),
    );
  }
}