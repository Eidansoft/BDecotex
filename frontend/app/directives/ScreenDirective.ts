/// <reference path="../../typings/angularjs/angular.d.ts" />

class ScreenDirective implements ng.IDirective {
    restrict = 'A';
//    require = 'ngModel';
    templateUrl = 'app/directives/screenDirective.html';
//    replace = true;

    constructor() {
    }

    link = (scope: ng.IScope, element: ng.IAugmentedJQuery, attrs: ng.IAttributes, ctrl: any) => {
    }

    static factory(): ng.IDirectiveFactory {
        const directive = () => new ScreenDirective();
        directive.$inject = [];
        return directive;
    }
}

bdecotexApp.directive(
    'myCustomer', ScreenDirective.factory());

//class BDecotexScreenController
//{
//    static dependencies = [BDecotexScreenController];
//    protected waitingScreen: boolean;
//    protected messageScreen: boolean;
//
//    constructor(){
//        this.waitingScreen = false;
//        this.messageScreen = false;
//    }
//
//    public showWaitingScreen()
//    {
//        this.waitingScreen = true;
//    }
//
//    public hideWaitingScreen()
//    {
//        this.waitingScreen = false;
//    }
//
//    public showMessageScreen()
//    {
//        this.messageScreen = true;
//    }
//
//    public hideMessageScreen()
//    {
//        this.messageScreen = false;
//    }
//}
//
//// Register the controller with Angular
//bdecotexApp.controller(
//	'BDecotexScreenController', BDecotexScreenController.dependencies);
//
//

//
//app.directive('ScreenDirective', ScreenDirective.factory());