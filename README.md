# SmartCalc_v2.0

Implementation of SmartCalc v2.0 by OOP and using MVP-pattern.

## Introduction

In this project I've implemented an extended version of the standard calculator in C++ in the object-oriented programming paradigm, implementing the same functions as the previously developed application in SmartCalc v1.0 project (https://github.com/Colonka/s21_calc_V1.0). This calculator version is implemented by MVC-pattern(The Model-View-Controller (MVC) pattern is a scheme of separating application modules into three macro-components: a model that contains the business logic, a view that is a UI form to interact with the program, and a controller that modifies the model by user action.)

All detailed information you can find here: https://github.com/Colonka/s21_calc_V1.0

## Instructons for running

Being in `src` folder run command `make` and then `make run`.

## Instruction for archiving

Being in `src` folder run command `make dist` that create folder with archived calculator.

## Instruction for testing

Being in `src` folder run command `make test`

*Note: you need installed `pkg-config` for choosing flags for gtest library linking.

## Instruction for gcovr test coverage

Being in `src` folder run command `make gcovr_report`

## Documentation

To open library documentation run command `make docs` in terminal being in `src` folder.