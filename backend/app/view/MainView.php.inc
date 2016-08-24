<?php
require_once (dirname(__FILE__).'/BDecotexView.php');
require_once (dirname(__FILE__).'/FamilyView.php.inc');
require_once (dirname(__FILE__)."/SexView.php.inc");
require_once (dirname(__FILE__)."/LineView.php.inc");
require_once (dirname(__FILE__)."/ModelView.php.inc");
require_once (dirname(__FILE__).'/../libs/fastRoute/bootstrap.php');

/**
 * Description of FamilyView
 *
 * @author alex
 */
class MainView extends BDecotexView{
    const VIEW_FAMILY = 0;
    const VIEW_SEX = 1;
    const VIEW_LINE = 2;
    const VIEW_MODEL = 3;
    
    protected $httpMethod;
    protected $uri;

    public function __construct() {
        $dispatcher = FastRoute\simpleDispatcher(function(FastRoute\RouteCollector $r) {
            $r->addRoute(['GET', 'POST', 'DELETE', 'PUT'], '/bdecotex/family[/{params:.+}]', MainView::VIEW_FAMILY);
            $r->addRoute(['GET', 'POST', 'DELETE', 'PUT'], '/bdecotex/sex[/{params:.+}]', MainView::VIEW_SEX);
            $r->addRoute(['GET', 'POST', 'DELETE', 'PUT'], '/bdecotex/line[/{params:.+}]', MainView::VIEW_LINE);
            $r->addRoute(['GET', 'POST', 'DELETE', 'PUT'], '/bdecotex/mod[/{params:.+}]', MainView::VIEW_MODEL);
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
            case MainView::VIEW_LINE:
                $view = new LineView();
                $view->processUri($this->httpMethod, $this->uri);
                break;
            case MainView::VIEW_MODEL:
                $view = new ModelView();
                $view->processUri($this->httpMethod, $this->uri);
                break;
        }
    }
}
