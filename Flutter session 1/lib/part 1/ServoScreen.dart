import 'package:flutter/material.dart';

class ServoScreen extends StatefulWidget {
  const ServoScreen({super.key});

  @override
  State<ServoScreen> createState() => _SliderExampleState();
}

class _SliderExampleState extends State<ServoScreen> {
  double _currentSliderValue = 0;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Servo Angle')),
      body: Column(
        mainAxisAlignment: MainAxisAlignment.spaceEvenly,
        children: [
          Text("Enter the Servo angle!", style: TextStyle(fontSize: 40)),
          Text("The Angle: "+_currentSliderValue.toStringAsFixed(1), style: TextStyle(fontSize: 20)),
          Slider(
              value: _currentSliderValue,
              min: 0,
              max: 180,
              label: _currentSliderValue.toStringAsFixed(1),
              //activeColor: Colors.lightBlue,
              //inactiveColor: Colors.lightBlueAccent,
              onChanged: (value){
                setState(() {
                  _currentSliderValue = value;
                });
              },

          ),
        ],
      )
    );
  }
}
