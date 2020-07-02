#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "TP-LINK_OG"
#define STAPSK  "097226437"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

const int led = 13;

int PinRED = 0;
int PinGREEN = 2;
int PinBLUE = 4;

void handleRoot() {
  server.send(200, "text/html", "<!doctype html><html lang='en' ng-app='recipesApp'><head><meta charset='utf-8'><title> Rezepte APP</title> <script src='https://ajax.googleapis.com/ajax/libs/angularjs/1.6.9/angular.min.js'></script> <script src='https://ajax.googleapis.com/ajax/libs/angularjs/1.6.9/angular-route.js'></script> <script>var recipesApp=angular.module('recipesApp',['ngRoute']);angular.module('recipesApp').config(['$routeProvider',function config($routeProvider){$routeProvider.when('/detail/:recipeId',{template:'<recipe-detail></recipe-detail>'}).when('/',{template:'<recipe-list></recipe-list>'}).otherwise('/');}]);angular.module('recipesApp').component('recipeDetail',{templateUrl:'template?template=recipeDetail',controller:['$routeParams',function IngredientsListController($routeParams){this.id=$routeParams.recipeId;this.recipe=[{name:'Nudeln'},{name:'Reis'}];}]});angular.module('recipesApp').component('recipeList',{templateUrl:'template?template=recipeList',controller:function RecipesList(){this.recipes=[{name:'Nudeln',time:'15 min',id:0},{name:'Reis',time:'30min',id:1}];}});</script> </head><body><div ng-view></div></body></html>");
}


void handleTemplates() { //Handler

  String templateData = "";
  String urlParam = server.arg(0);
  if(urlParam == "recipeDetail"){
    templateData = "<a href='#!/home/'> <- back </a><h1> {{ $ctrl.recipe[$ctrl.id].name }}</h1>";
  }
  if(urlParam == "recipeList"){
    templateData = "Search: <input ng-model='$ctrl.query' /><ul><li ng-repeat='recipe in $ctrl.recipes | filter:$ctrl.query'> <a href='#!/detail/{{recipe.id}}'> <span>{{recipe.name}}</span><p>{{recipe.time}}</p> </a></li></ul>";
  }
  
  server.send(200, "text/html", templateData);       //Response to the HTTP request

}


// LED functions :
void red(){
  digitalWrite(PinRED, HIGH); // HIGH = an, LOW = aus
  digitalWrite(PinGREEN, LOW);
  digitalWrite(PinBLUE, LOW);
}

void green(){
  digitalWrite(PinRED, LOW);
  digitalWrite(PinGREEN, HIGH);
  digitalWrite(PinBLUE, LOW);
}

void pink(){
  digitalWrite(PinRED, HIGH);
  digitalWrite(PinGREEN, LOW);
  digitalWrite(PinBLUE, HIGH);
}

void cyan(){
  digitalWrite(PinRED, LOW);
  digitalWrite(PinGREEN, HIGH);
  digitalWrite(PinBLUE, HIGH);
}


// LED functions |

void setup(void) {
  pinMode(PinRED, OUTPUT);
  pinMode(PinGREEN, OUTPUT);
  pinMode(PinBLUE, OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  if (MDNS.begin("www.test.local")) {
    cyan();
  }

  server.on("/", handleRoot);

  server.on("/template", handleTemplates);

  server.onNotFound(handleRoot);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}
