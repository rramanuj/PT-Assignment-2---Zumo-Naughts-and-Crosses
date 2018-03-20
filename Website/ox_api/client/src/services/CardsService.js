import API from '@/services/API'


export default {
        getCardsByProject (projectId, board) {
            return API().post('CardsByProject', projectId, board);          //post method of Axios module. 
    },
          updateBoard (_id, board) {
        return API().put('editBoard', _id, board);          //post method of Axios module. 
        },
        getCardById (cardId) {
                return API().post('getCardById', cardId);          //post method of Axios module. 
        },
        edit(_id, title, description, owner, deadline) {
                return API().put('editCard', _id, title, description, owner, deadline);
        },
        delete(_id, isDeleted){
                return API().put('deleteCard', _id, isDeleted);
        }
}


