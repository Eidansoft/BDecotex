interface IScreenDirectiveScope extends ng.IScope{
//    hideModal:()=>void;
    waitingScreen: boolean;
    messages: Array<MessageScreen>;
    closeAlert: Function;
}

class MessageScreen {
    title: string;
    msg: string;
    level: string;
    
    constructor(msg:string, level?:string, title?:string){
        this.msg = msg;
        if (title !== undefined){
            this.title = title;
        }
        this.level = "warning";
        if (level !== undefined && (level == 'success' || level == 'info' || level == 'warning' || level == 'danger')){
            this.level = level;
        }
    }
}

class ScreenDirective implements ng.IDirective {
    public restrict: string = 'A';
    public templateUrl: string = 'app/directives/screenDirective.html';
    link: Function = (scope: IScreenDirectiveScope, element: ng.IAugmentedJQuery, attrs: ng.IAttributes, ctrl: any) => {
        let showWaitingScreen = function(data, message):any{
            scope.waitingScreen = true;
        }
        this.pubsubHandler.subscribe('SHOW_WAITING_SCREEN', showWaitingScreen);
        
        let hideWaitingScreen = function(data, message):any{
            scope.waitingScreen = false;
        }
        this.pubsubHandler.subscribe('HIDE_WAITING_SCREEN', hideWaitingScreen);
        
        scope.messages = new Array;
        let addMessage = function(data: MessageScreen, message):any{
            scope.messages.push(data);
        }
        this.pubsubHandler.subscribe('SHOW_MESSAGE', addMessage);
        
        scope.closeAlert = function(index) {
            scope.messages.splice(index, 1);
        };
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
