import 'dart:async';
import 'package:flutter/material.dart';
import 'package:charts_flutter/flutter.dart' as charts;
import 'package:first_app/servo_screen.dart';
import 'package:first_app/login_screen.dart';
import 'dart:math';

class SensorApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Sensor App',
      theme: ThemeData(
        primarySwatch: Colors.purple,
      ),
      home: DashboardScreen(),
    );
  }
}

class DashboardScreen extends StatefulWidget {
  @override
  _DashboardScreenState createState() => _DashboardScreenState();
}

class _DashboardScreenState extends State<DashboardScreen> {
  List<charts.Series<SensorReading, DateTime>> seriesList = [];
  List<SensorReading> chartData = [];
  final Random random = Random();
  final chartColor = charts.MaterialPalette.purple.shadeDefault;

  @override
  void initState() {
    super.initState();
    // Initialize chart data with dummy values
    chartData = [
      SensorReading(DateTime.now().subtract(Duration(seconds: 5)), 0),
      SensorReading(DateTime.now().subtract(Duration(seconds: 4)), 5),
      SensorReading(DateTime.now().subtract(Duration(seconds: 3)), 10),
      SensorReading(DateTime.now().subtract(Duration(seconds: 2)), 8),
      SensorReading(DateTime.now().subtract(Duration(seconds: 1)), 2),
    ];

    seriesList = [
      charts.Series<SensorReading, DateTime>(
        id: 'Sensor Readings',
        colorFn: (_, __) => chartColor,
        domainFn: (SensorReading reading, _) => reading.time,
        measureFn: (SensorReading reading, _) => reading.value,
        data: chartData,
      )
    ];

    // Simulate real-time updates to the chart data
    Timer.periodic(Duration(seconds: 1), (timer) {
      setState(() {
        // Generate a random value
        final newValue = random.nextInt(10);
        final newTime = DateTime.now();

        // Add the new reading to the chart data
        chartData.add(SensorReading(newTime, newValue));

        // Remove old readings (keep only the last 5 seconds)
        chartData.removeWhere((reading) =>
            reading.time.isBefore(newTime.subtract(Duration(seconds: 5))));

        // Update the series list
        seriesList = [
          charts.Series<SensorReading, DateTime>(
            id: 'Sensor Readings',
            colorFn: (_, __) => chartColor,
            domainFn: (SensorReading reading, _) => reading.time,
            measureFn: (SensorReading reading, _) => reading.value,
            data: chartData,
          )
        ];
      });
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        leading: IconButton(
          icon: Icon(Icons.arrow_back),
          onPressed: () {
            Navigator.push(context,
              MaterialPageRoute(builder: (context) => LoginScreen()),
            );
          },
        ),
        title: Text('Sensor Readings'),
      ),
      body: Column(
        children: [
          Expanded(
            flex: 4,
            child: Container(
              padding: EdgeInsets.all(16.0),
              child: charts.TimeSeriesChart(
                seriesList,
                animate: true,
              ),
            ),
          ),
          Expanded(
            flex: 1,
            child: Container(
              alignment: Alignment.center,
              child: StreamBuilder<SensorReading>(
                stream: chartData.isNotEmpty
                    ? Stream.value(chartData.last)
                    : Stream.empty(),
                builder: (context, snapshot) {
                  if (snapshot.hasData) {
                    final reading = snapshot.data!;
                    return Text(
                      'Current Reading: ${reading.value}',
                      style: TextStyle(fontSize: 20.0),
                    );
                  } else {
                    return Text(
                      'Waiting for data...',
                      style: TextStyle(fontSize: 20.0),
                    );
                  }
                },
              ),
            ),
          ),
        ],
      ),
      floatingActionButton: FloatingActionButton(
          onPressed: () {
            Navigator.push(context,
              MaterialPageRoute(builder: (context) => const ServoScreen()),
            );
          },
        child: const Icon((Icons.account_balance_sharp)),
      ), // This trailing comma makes auto-formatting nicer for build methods
    );
  }
}

class SensorReading {
  final DateTime time;
  final int value;

  SensorReading(this.time, this.value);
}