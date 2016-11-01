// BDecotex APP

// Configuration of the routing
routeConfig.$inject = ["$routeProvider"];
function routeConfig($routeProvider: ng.route.IRouteProvider): void{
   $routeProvider
      .when("/family", {
         templateUrl: "app/view/viewFamily.html",
         controller: "ControllerFamily as data"
      })
      .when("/line", {
         templateUrl: "app/view/viewLine.html",
         controller: "ControllerLine as data"
      })
      .when("/sex", {
         templateUrl: "app/view/viewSex.html",
         controller: "ControllerSex as data"
      })
      .when("/model", {
         templateUrl: "app/view/viewModel.html",
         controller: "ControllerModel as data"
      })
      .when("/storeDetails/:storeId", {
         templateUrl: "/templates/storeDetailView.html",
         controller: "StoreDetailCtrl as vm"
      })
      .otherwise("/family");
}

let bdecotexApp = angular.module('bdecotex',  [
    'ngRoute',
    'PubSub',
    'ui.grid',
    'ui.grid.selection',
    'ui.select'
//        require('angular-ui-router'),
//        require('angular-animate'),
//        require('angular-ui-bootstrap'),
//        require('angular-translate')
    ]);
bdecotexApp.config(routeConfig);
// Hay un problema con las dependencias del BackendService que no me deja
// ponerlas como las del controller