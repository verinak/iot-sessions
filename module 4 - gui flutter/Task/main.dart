import 'package:practice1/SecondScreen.dart';
import 'package:flutter/material.dart';

void main() {
  runApp(MyApp());
}

class Task {
  final String title;
  bool isCompleted;

  Task(this.title, {this.isCompleted = false});
}
class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'To-Do List App',
      theme: ThemeData(
        primarySwatch: Colors.pink,
      ),
      home: MyHomePage(),
    );
  }
}
class MyHomePage extends StatefulWidget {
  @override
  _MyHomePageState createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  List<Task> tasks = [
    Task('Finish training session'),
    Task('Finish Tasks'),
    Task('Go HOME'),
  ];

  void toggleTaskCompletion(int index) {
    setState(() {
      tasks[index].isCompleted = !tasks[index].isCompleted;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('To-Do List'),
        backgroundColor: Color(0xffde7acd),

      ),

      body: Column(
        children: [
          Expanded(child: ListView.builder(
            itemCount: tasks.length,
            itemBuilder: (BuildContext context, int index) {
              return ListTile(
                title: Text(tasks[index].title),
                trailing: Checkbox(value: tasks[index].isCompleted,
                  onChanged: (value) => toggleTaskCompletion(index),
                ),
              );
            },
          ),
          ),
          ElevatedButton(onPressed: () {
            Navigator.push(context,
              MaterialPageRoute(builder: (context) => SecondScreen()),
            );
          },
            child: Text("Go to Second Screen"),
          ),
        ],
      ),
    );
  }
}

// Column