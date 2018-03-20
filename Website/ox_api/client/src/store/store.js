//vuex is essentially vuex's flux, this is used ot keep track of constants throughout the application

import Vue from 'vue';
import Vuex from 'vuex';
import createPersistedState from 'vuex-persistedstate'

Vue.use(Vuex);
//global states of our application and can be used for adding stuff to headers/changing whats dispayed etc.
export default new Vuex.Store({
    strict: true, //you cant modify the state unless its through a mutation
    plugins: [createPersistedState()],
    state: {
        token: null,
        user: null,
        isUserLoggedIn: false
    },
    mutations: {
        setToken (state, token) {
            state.token = token
            if(token){
                state.isUserLoggedIn = true
            }
            else{
                state.isUserLoggedIn = false
            }
        },
        setUser (state, user) {
            state.user = user
        }
    },
    actions: {
        //always invoke actions from vue components
        setToken ( {commit}, token) {
            commit('setToken', token)
        },
        setUser ({commit}, user) {
            commit('setUser', user)
        }
    }
})