module.exports = {
    credentialSecret: process.env.NODE_RED_CREDENTIAL_SECRET,
    uiPort: process.env.PORT || 1880,

    httpAdminRoot: "/",
    httpNodeRoot: "/",

    functionGlobalContext: {},

    logging: {
        console: {
            level: "info",
            metrics: false,
            audit: false
        }
    }
};
