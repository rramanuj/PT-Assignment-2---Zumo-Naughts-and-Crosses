// this is the code how we hit different urls/

import Vue from 'vue';
import Router from 'vue-router';
import HelloWorld from '@/components/HelloWorld';
import Register from '@/components/Register';
import Login from '@/components/Login';
import Projects from '@/components/Projects/Index';
import AddCard from '@/components/Cards/AddCard';
import ViewCard from '@/components/Cards/ViewCard';
import AddComment from '@/components/Cards/AddComment';

Vue.use(Router);

export default new Router({
  routes: [
    {
      path: '/',
      name: 'home',
      component: HelloWorld,
    },
    {
      path: '/projects',
      name: 'projects',
      component: Projects,
    },
    {
      path: '/register',
      name: 'register',
      component: Register,
    },
    {
      path: '/dashboard',
      name: 'dashboard',
      component: Projects,
    },
    {
      path: '/viewCard',
      name: 'view-card',
      component: ViewCard,
    },
    {
      path: '/addCard/:projectId',
      name: 'add-card',
      component: AddCard,
    },
    {
      path: '/card/:cardId:projectId',
      name: 'card',
      component: ViewCard,
    },
    {
      path: '/addComment/:cardId:projectId',
      name: 'add-comment',
      component: AddComment,
    },
    {
      path: '/login',
      name: 'login',
      component: Login,
    },
    {
      path: '/*',
      redirect: 'home'
    },
  ],
});
