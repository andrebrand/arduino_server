
        // Define the `recipesApp` module
        var recipesApp = angular.module('recipesApp', ['ngRoute']);
        
        angular.
        module('recipesApp').
        config(['$routeProvider',
            function config($routeProvider) {
            $routeProvider.
                when('/detail/:recipeId', {
                template: '<recipe-detail></recipe-detail>'
                }).
                when('/', {
                template: '<recipe-list></recipe-list>'
                }).
                otherwise('/');
            }
        ]);

        angular.
        module('recipesApp').
        component('recipeDetail', {  // This name is what AngularJS uses to match to the `<recipe>` element.
            template:
                '<a href="#!/home/">' +
                    '<- back'+
                '</a>'+
                '<h1> {{ $ctrl.recipe[$ctrl.id].name }} </h1>'
                
                ,
            controller: ['$routeParams', function IngredientsListController($routeParams) {
                this.id = $routeParams.recipeId;
                this.recipe = [
                    {name: 'Nudeln'},
                    {name: 'Reis'}
                ];
            }]
        });

        angular.
        module('recipesApp').
        component('recipeList', {  // This name is what AngularJS uses to match to the `<recipe-list>` element.
            template:
                '  Search: <input ng-model="$ctrl.query" />' +
                '<ul>' +
                '<li ng-repeat="recipe in $ctrl.recipes | filter:$ctrl.query">' +
                    '<a href="#!/detail/{{recipe.id}}">' +
                        '<span>{{recipe.name}}</span>' +
                        '<p>{{recipe.time}}</p>' +
                    '</a>' +
                '</li>' +
                '</ul>',
            controller: function RecipesList() {
                this.recipes = [
                    {
                        name: 'Nudeln',
                        time: '15 min',
                        id: 0
                    }, 
                    {
                        name: 'Reis',
                        time: '30min',
                        id: 1
                    }
                ];
            }
        });