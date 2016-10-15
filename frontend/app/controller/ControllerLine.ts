class ControllerLine
{
    static dependencies = [ControllerLine];
    
    constructor()
    {
        
    }

}

// Register the controller with Angular
bdecotexApp.controller(
	'ControllerLine', ControllerLine.dependencies);
