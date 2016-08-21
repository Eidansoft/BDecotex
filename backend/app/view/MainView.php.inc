<?php
require_once (dirname(__FILE__).'/BDecotexView.php');
require_once "./FamilyView.php.inc";
require_once (dirname(__FILE__)."/SexView.php.inc");
require_once "../libs/fastRoute/bootstrap.php";

/**
 * Description of FamilyView
 *
 * @author alex
 */
class MainView extends BDecotexView{
    const VIEW_FAMILY = 0;
    const VIEW_SEX = 1;
    
    protected $httpMethod;
    protected $uri;

    public function __construct() {
        $dispatcher = FastRoute\simpleDispatcher(function(FastRoute\RouteCollector $r) {
            $r->addRoute(['GET', 'POST', 'DELETE', 'PUT'], '/bdecotex/family[/{params:.+}]', MainView::VIEW_FAMILY);
            $r->addRoute(['GET', 'POST', 'DELETE', 'PUT'], '/bdecotex/sex[/{params:.+}]', MainView::VIEW_SEX);
        });
        parent::__construct($dispatcher);
    }
    
    public function processUri($httpMethod, $uri) {
        $this->httpMethod = $httpMethod;
        $this->uri = $uri;
        parent::processUri($httpMethod, $uri);
    }

    protected function processHandler($handler, $vars) {
        switch ($handler) {
            case MainView::VIEW_FAMILY:
                $view = new FamilyView();
                $view->processUri($this->httpMethod, $this->uri);
                break;
            case MainView::VIEW_SEX:
                $view = new SexView();
                $view->processUri($this->httpMethod, $this->uri);
                break;
        }
    }
}
