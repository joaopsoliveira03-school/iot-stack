CREATE TABLE IF NOT EXISTS measurements (
    ts TIMESTAMP WITH TIME ZONE DEFAULT NOW() NOT NULL,
    payload TEXT
);
INSERT INTO measurements (payload) ("{{{payload}}}");