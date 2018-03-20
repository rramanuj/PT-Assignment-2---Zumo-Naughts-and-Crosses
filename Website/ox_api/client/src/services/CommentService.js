import API from '@/services/API'


export default {
  post(cardId, userId, text) {
    return API().post('comment', cardId, userId, text); // post method of Axios module.
  },
  delete(_id, isDeleted) {
    return API().put('deleteComment', _id, isDeleted);
}
};

