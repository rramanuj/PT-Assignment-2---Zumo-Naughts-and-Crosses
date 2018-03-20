import API from '@/services/API'


export default {
    // index(search) {
    //     return API.get('projects', {
    //         params: {search: search}
    //     })
    // },
        getProjectsByUser (userId) {
            return API().post('projectsByUser', userId);          //post method of Axios module. 
    },
        post (project) {
            return API().post('newProject', project);
        },
        show (projectId) {
            return API().post('getProjectById', projectId);
        },
        drop (projectId) {
            return API().put('drop', projectId);
        },
        addMember (projectId, userId) {
            return API().put('addTeamMember', projectId, userId);
        },
        removeMember (projectId, userId) {
            return API().put('removeMember', projectId, userId);
        },
        getTeam (projectId) {
            return API().post('getProjectTeam', projectId);
        },
        search (userId, query) {
            return API().put('search', userId, query);
        },
        postCard (projectId, title, description, deadline, userId, owner, board) {
            return API().post('newCard', projectId, title, description, deadline, userId, owner, board);
        }
}


