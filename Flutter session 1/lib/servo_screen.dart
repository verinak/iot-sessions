import 'package:flutter/material.dart';
import 'package:first_app/login_screen.dart';

class ServoScreen extends StatefulWidget {
  const ServoScreen({Key? key}) : super(key: key);

  @override
  State<ServoScreen> createState() => _ServoScreenState();
}

class _ServoScreenState extends State<ServoScreen> {
  double _currentSliderValue = 0;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Servo Angle')),
      body: Container(
        decoration: BoxDecoration(
          image: DecorationImage(
            image: AssetImage('lib/assets/images/img_3.png'),
            fit: BoxFit.cover,
          ),
        ),
        child: Column(
          mainAxisAlignment: MainAxisAlignment.spaceEvenly,
          children: [
            Text(
              "Enter the Servo angle!",
              style: TextStyle(fontSize: 35),
            ),
            Text(
              "Servo Angle: " + _currentSliderValue.toStringAsFixed(1),
              style: TextStyle(fontSize: 20),
            ),
            Slider(
              value: _currentSliderValue,
              min: 0,
              max: 180,
              label: _currentSliderValue.toStringAsFixed(1),
              onChanged: (value) {
                setState(() {
                  _currentSliderValue = value;
                });
              },
            ),
          ],
        ),
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: () {
          Navigator.push(
            context,
            MaterialPageRoute(builder: (context) => LoginScreen()),
          );
        },
        child: const Icon(Icons.account_circle_rounded),
      ),
    );
  }
}