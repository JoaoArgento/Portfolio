let programmingTexts = {
    Csharp: ["using System;", 'Person person = new Person("João", 22, 1.75);', 'Console.WriteLine($"{person.name}");'],
    C: ["#include <stdio.h>", 'Person person = {"João", 22, 1.75};', 'printf("%s", person.name);'],
    Cplusplus: ["#include <iostream>", 'Person * person = new Person("João", 22, 1.75);', 'std::cout << person->name << std::endl;'],
    Unity: ["using UnityEngine;", 'Person person = new Person("João", 22, 1.75);', 'Debug.Log($"{person.name}");'],
    Godot: ["extends Node2D", 'var person = Person("João", 22, 1.75)', 'print(person.name)'],
    Javascript: ['const person = {name: "Joao", age: 22, height: 1.75}', "console.log(person.name)"]
}
export default {programmingTexts}