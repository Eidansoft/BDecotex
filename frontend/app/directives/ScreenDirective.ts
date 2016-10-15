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
