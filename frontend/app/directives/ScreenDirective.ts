interface IScreenDirectiveScope extends ng.IScope{
//    hideModal:()=>void;
    waitingScreen: boolean;
}

class ScreenDirective implements ng.IDirective {
    public restrict: string = 'A';
    public templateUrl: string = 'app/directives/screenDirective.html';
    link: Function = (scope: IScreenDirectiveScope, element: ng.IAugmentedJQuery, attrs: ng.IAttributes, ctrl: any) => {
        let showWaitingScreen = function(message, data):any{
            scope.waitingScreen = true;
        }
        
        let hideWaitingScreen = function(message, data):any{
            scope.waitingScreen = false;
        }
        
        this.pubsubHandler.subscribe('SHOW_WAITING_SCREEN', showWaitingScreen);
        this.pubsubHandler.subscribe('HIDE_WAITING_SCREEN', hideWaitingScreen);
    };
    //public require = 'ngModel';

    private pubsubHandler: any;
    
    constructor(PubSub: any) {
        this.pubsubHandler = PubSub;
    }

    static factory(): ng.IDirectiveFactory {
        const directive = (PubSub: any) => {
            return new ScreenDirective(PubSub);
        };
        directive.$inject = ['PubSub'];
        return directive;
    }
}

bdecotexApp.directive(
    'directiveScreen', ScreenDirective.factory());
